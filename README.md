# Smart Home Security System  
![GitHub Logo](https://github.githubassets.com/images/modules/logos_page/GitHub-Mark.png)

## Table of Contents
1. [Introduction](#introduction)  
2. [Components](#components)  
3. [System Architecture](#system-architecture)  
    - [3.1 Door Security Module](#31-door-security-module)  
    - [3.2 Window Security Module](#32-window-security-module)  
    - [3.3 Fire Detection Module](#33-fire-detection-module)  
    - [3.4 Gas Leak Detection Module](#34-gas-leak-detection-module)  
    - [3.5 Light Control Module](#35-light-control-module)  
4. [Communication & Integration](#communication--integration)  
5. [System Workflow](#system-workflow)  

---

## Introduction  
**Objective:** Provide cost-effective security for people and property inside the house.  
**Motivation:** High-end security systems are often expensive and not accessible to everyone. This project aims to create an affordable solution with key functionalities such as motion detection, alarms, AI-based recognition, and real-time notifications via a mobile app.  

---

## Components  
- **Micro Servo Motor:** For door control.  
- **Switch:** To trigger manual actions.  
- **RFID Card Reader:** For authorized entry.  
- **IR Sensor:** For detecting window intrusions.  
- **MQ2 Gas Sensor:** For detecting gas leaks.  
- **Real-Time Clock (RTC) Module:** To schedule tasks and log events.  
- **Buzzer:** For audio alerts.  
- **LCD Screen:** To display messages (e.g., welcome messages for authorized users).  
- **ESP-32 Wi-Fi & Bluetooth Module:** For wireless communication.  
- **DHT11 Temperature and Humidity Sensor:** For monitoring indoor climate and fire detection.  
- **IoT Development Boards:** Two Arduino Uno boards for managing different sensors and functionalities.  
- **Web Camera:** For AI-based person recognition.  

---

## System Architecture  

### 3.1 Door Security Module  
**Components:** Micro Servo Motor, RFID Reader, Buzzer, LCD Screen, Camera (for AI).  
**Functionalities:**  
- AI-based person recognition to allow/deny entry.  
- RFID card reader for secure access.  
- Automatic door control (opens if recognized or authorized).  
- Display welcome message on the LCD.  
- Buzzer sounds if unauthorized access is detected.  

### 3.2 Window Security Module  
**Components:** IR Sensor, Buzzer, ESP-32 Module.  
**Functionalities:**  
- IR sensor detects window intrusions.  
- Sends an alarm notification to the mobile app.  
- Buzzer sounds for immediate audio alert.  
- Updates window status (open/closed) on the app.  

### 3.3 Fire Detection Module  
**Components:** DHT11 Temperature and Humidity Sensor, ESP-32 Module.  
**Functionalities:**  
- Monitors temperature and humidity inside the house.  
- If temperature exceeds 40°C, system assumes a fire.  
- Sends real-time notification to the app with a warning.  
- Updates temperature and humidity values on the app for monitoring.  

### 3.4 Gas Leak Detection Module  
**Components:** MQ2 Gas Sensor, Buzzer, ESP-32 Module.  
**Functionalities:**  
- Monitors gas levels in the house, specifically in the kitchen.  
- If the gas level crosses a defined threshold, the system detects a gas leak.  
- Rings the buzzer and sends a real-time warning notification to the app.  

### 3.5 Light Control Module  
**Components:** ESP-32 Module, Mobile App.  
**Functionalities:**  
- Users can remotely control lights via the mobile app.  
- The system updates the light status (on/off) in real-time on the app.  

---

## Communication & Integration  
**Mobile App:** Central hub for all notifications and controls (real-time updates, lights, window, fire, and gas alerts).  
**ESP-32 Wi-Fi & Bluetooth Module:** Handles communication between the mobile app and the system components.  
- Sends real-time alerts (door security, gas leak, fire detection).  
- Enables remote control of lights via the app.  

### 4.1 Dual Arduino Boards  
- **Arduino 1 (Board 1):** Dedicated to controlling the door and associated components (Servo, RFID, Camera, LCD).  
- **Arduino 2 (Board 2):** Handles all other sensors (IR for window, MQ2 for gas, DHT11 for fire detection, light control).  
- Connected to the ESP-32 for wireless communication.  

---

## System Workflow  

### Entry Attempt at Main Door:  
1. Camera uses AI to detect the person.  
2. If recognized, the RFID system checks for authorization.  
3. Servo motor opens the door, and LCD displays a welcome message.  
4. If unauthorized, the buzzer rings and a notification is sent to the mobile app.  

### Window Intrusion:  
1. IR sensor detects an attempt to open the window.  
2. Buzzer sounds, and an alert is sent to the app.  
3. The window status is updated (open/closed) in real-time on the app.  

### Fire Detection:  
1. DHT11 sensor continuously monitors temperature and humidity.  
2. If temperature exceeds 40°C, a fire warning is sent to the app.  
3. The system displays current temperature and humidity in the app.  

### Gas Leak Detection:  
1. MQ2 sensor monitors gas levels in the house.  
2. If levels exceed a safe threshold, the buzzer sounds and an alert is sent to the app.  
3. Real-time gas monitoring is updated in the app.  

### Light Control:  
1. The user can turn lights on/off remotely through the app.  
2. Status is updated in the app in real-time.  

---

## License  
This project is licensed under the MIT License.  
