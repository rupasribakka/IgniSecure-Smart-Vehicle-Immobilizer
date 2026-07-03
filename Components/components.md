# 🔧 Hardware Components

The IgniSecure system is built using low-cost IoT hardware components to provide vehicle security, GPS tracking, and remote monitoring.

| Component | Description |
|-----------|-------------|
| ESP32 Microcontroller | Main controller that manages all hardware components and Wi-Fi communication. |
| GPS Module (Neo-6M) | Provides real-time vehicle location (Latitude & Longitude). |
| 4x3 Matrix Keypad | Used for entering the security password. |
| 16x2 LCD Display (I2C) | Displays system status, password prompts, and alerts. |
| Buzzer | Generates an alarm for incorrect password attempts and security notifications. |
| DC Motor | Represents the vehicle engine for prototype demonstration. |
| Relay Module | Controls ON/OFF operation of the vehicle motor. |
| Breadboard | Used for circuit prototyping. |
| Jumper Wires | Connect all hardware components together. |
| USB Power Supply / Power Bank | Powers the ESP32 development board. |

---

# 💻 Software Requirements

| Software | Purpose |
|----------|---------|
| Arduino IDE | Writing, compiling, and uploading code to the ESP32. |
| ThingSpeak Cloud | Stores GPS coordinates and vehicle status remotely. |
| Wi-Fi Network | Connects the ESP32 to the cloud platform. |
| Google Maps | Displays the live GPS location of the vehicle. |


---

# 📌 Purpose

The above components work together to provide:

- 🔐 Password-based vehicle authentication
- 📍 Real-time GPS tracking
- 🌐 Cloud monitoring using ThingSpeak
- 🚨 Theft alert using buzzer
- 🚗 Vehicle immobilization after multiple incorrect password attempts
- 📲 Remote monitoring and control