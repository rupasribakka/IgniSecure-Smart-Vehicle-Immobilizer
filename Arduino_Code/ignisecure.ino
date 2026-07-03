/*
Project Name : IgniSecure
Description  : Smart Vehicle Immobilizer & Theft Alert System

Features:
✔ Password Authentication
✔ GPS Tracking
✔ ThingSpeak Cloud Monitoring
✔ Wi-Fi Connectivity
✔ LCD Display
✔ Keypad Access
✔ Vehicle Immobilizer
✔ Buzzer Alert

Hardware:
- ESP32
- GPS Module
- 4x3 Keypad
- 16x2 I2C LCD
- Relay Module
- Buzzer

Software:
- Arduino IDE

==========================================================
*/

#include <WiFi.h>
#include <ThingSpeak.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

//================ Wi-Fi & ThingSpeak =================//

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";

unsigned long WRITE_CHANNEL = YOUR_WRITE_CHANNEL;
unsigned long READ_CHANNEL  = YOUR_READ_CHANNEL;

const char* WRITE_API = "YOUR_WRITE_API_KEY";

const int READ_FIELD = 1;

WiFiClient client;

//================ LCD =================//

LiquidCrystal_I2C lcd(0x27, 16, 2);

//================ Keypad =================//

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] =
{
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {32,33,25,26};
byte colPins[COLS] = {27,14,12};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//================ GPS =================//

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

#define RXD2 16
#define TXD2 17

//================ Output Pins =================//

#define MOTOR 15
#define BUZZER 4

//================ Variables =================//

String password = "1234";     // Default Password
String input = "";

int wrongCount = 0;

bool locked = false;
bool motorState = false;

unsigned long lastSend = 0;

//==================================================

void connectWiFi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    lcd.clear();
    lcd.print("Connecting WiFi");

    int t = 0;

    while (WiFi.status() != WL_CONNECTED && t < 15)
    {
        delay(500);
        lcd.print(".");
        t++;
    }

    lcd.clear();

    if (WiFi.status() == WL_CONNECTED)
    {
        lcd.print("WiFi Connected");
    }
    else
    {
        lcd.print("WiFi Failed");
    }

    delay(1000);
}

//==================================================

void motorOn()
{
    digitalWrite(MOTOR, HIGH);
    motorState = true;

    lcd.clear();
    lcd.print("Vehicle Started");
}

//==================================================

void motorOff()
{
    digitalWrite(MOTOR, LOW);
    motorState = false;

    lcd.clear();
    lcd.print("Vehicle Stopped");
}

//==================================================

void buzzerBeep(int n = 1)
{
    for(int i=0;i<n;i++)
    {
        ledcAttachPin(BUZZER,0);
        ledcWriteTone(0,2000);

        delay(200);

        ledcWriteTone(0,0);

        delay(100);
    }
}

//==================================================

void sendData(float lat,float lon,int status)
{
    if(WiFi.status()!=WL_CONNECTED)
        return;

    ThingSpeak.setField(1,lat);
    ThingSpeak.setField(2,lon);
    ThingSpeak.setField(3,status);

    ThingSpeak.writeFields(WRITE_CHANNEL,WRITE_API);
}

//==================================================

void checkRemoteStart()
{
    long remote = ThingSpeak.readFloatField(READ_CHANNEL,READ_FIELD);

    if(remote==1 && !locked)
    {
        lcd.clear();
        lcd.print("Remote Started");

        motorOn();

        delay(1000);
    }
}

//==================================================

void setup()
{
    Serial.begin(115200);

    gpsSerial.begin(9600,SERIAL_8N1,RXD2,TXD2);

    pinMode(MOTOR,OUTPUT);
    pinMode(BUZZER,OUTPUT);

    digitalWrite(MOTOR,LOW);

    lcd.begin();
    lcd.backlight();

    connectWiFi();

    ThingSpeak.begin(client);

    lcd.clear();
    lcd.print("Enter Password:");
}

//==================================================

void loop()
{
    while(gpsSerial.available())
    {
        gps.encode(gpsSerial.read());
    }

    float lat = gps.location.isValid() ? gps.location.lat() : 0.0;

    float lon = gps.location.isValid() ? gps.location.lng() : 0.0;

    if(millis()-lastSend > 15000)
    {
        int status = locked ? 1 : 0;

        sendData(lat,lon,status);

        checkRemoteStart();

        lastSend = millis();
    }

    if(locked)
    {
        lcd.setCursor(0,1);
        lcd.print("System Locked");

        motorOff();

        delay(1000);

        return;
    }

    char key = keypad.getKey();

    if(key)
    {
        if(key=='#')
        {
            if(input==password)
            {
                lcd.clear();
                lcd.print("Access Granted");

                motorOn();

                wrongCount = 0;
            }
            else
            {
                lcd.clear();
                lcd.print("Wrong Password");

                buzzerBeep(2);

                wrongCount++;

                motorOff();

                if(wrongCount>=3)
                {
                    locked = true;

                    lcd.clear();
                    lcd.print("System Locked!");

                    buzzerBeep(3);
                }
            }

            input="";

            delay(1000);

            lcd.clear();
            lcd.print("Enter Password:");
        }

        else if(key=='*')
        {
            input="";

            lcd.clear();
            lcd.print("Cleared");

            delay(500);

            lcd.clear();
            lcd.print("Enter Password:");
        }

        else
        {
            input += key;

            lcd.setCursor(0,1);
            lcd.print("Input: ");
            lcd.print(input);
        }
    }
}