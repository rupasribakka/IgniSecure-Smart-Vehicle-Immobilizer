# 🔌 ESP32 Hardware Connections

## ESP32 Pin Configuration

### 📍 GPS Module
| GPS Module | ESP32 Pin |
|------------|-----------|
| TX | GPIO16 (RX2) |
| RX | GPIO17 (TX2) |
| VCC | 3.3V |
| GND | GND |

---

### 🔢 4x3 Keypad

#### Row Connections

| Row | ESP32 Pin |
|------|-----------|
| R1 | GPIO32 |
| R2 | GPIO33 |
| R3 | GPIO25 |
| R4 | GPIO26 |

#### Column Connections

| Column | ESP32 Pin |
|---------|-----------|
| C1 | GPIO27 |
| C2 | GPIO14 |
| C3 | GPIO12 |

---

### 🚗 Motor / Relay Module

| Device | ESP32 Pin |
|--------|-----------|
| Relay IN | GPIO15 |
| VCC | 5V |
| GND | GND |

---

### 🔔 Buzzer

| Device | ESP32 Pin |
|--------|-----------|
| Positive (+) | GPIO4 |
| Negative (-) | GND |

---

### 📺 LCD Display (16x2 I2C)

| LCD Pin | ESP32 Pin |
|---------|-----------|
| SDA | GPIO21 |
| SCL | GPIO22 |
| VCC | 5V |
| GND | GND |

I2C Address: **0x27**

---

## 🌐 Cloud Platform

- **Cloud Service:** ThingSpeak
- **Microcontroller:** ESP32
- **Communication:** Wi-Fi
- **GPS Update Interval:** Every 15 seconds

---

## 📌 Working Flow

1. Power ON the ESP32.
2. Connect to Wi-Fi.
3. LCD displays **"Enter Password"**.
4. User enters the 4-digit password using the keypad.
5. If the password is correct:
   - Vehicle motor starts.
6. If the password is incorrect:
   - Buzzer sounds.
7. After 3 incorrect attempts:
   - System locks.
   - Vehicle motor stops.
8. GPS sends live latitude and longitude to ThingSpeak every 15 seconds.
9. Owner can monitor the vehicle remotely through the ThingSpeak dashboard.
10. Remote commands from ThingSpeak can be used to control the vehicle.

---

## 🛠 Software Used

- Arduino IDE
- ESP32 Board Package
- ThingSpeak Cloud
- Embedded C / Arduino Programming