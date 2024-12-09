# HOT AIR Station Controller

## Overview
The **HOT_AIR_Station** is a firmware designed to control a hot air rework station via a microcontroller-based system. This firmware integrates with sensors, temperature controls, and motor drivers to regulate air pressure and temperature. The system provides precise heat control for electronics soldering, PCB reworking, and similar applications.

This project is implemented using the **PlatformIO** environment for smooth development, testing, and deployment.

---

## Features
- **Precise Temperature Control:**  
  Using PID-based temperature feedback to ensure stable and accurate control.
  
- **Adjustable Hot Air Settings:**  
  Control motor speed, temperature settings, and airflow with ease.

- **User Interface Integration:**  
  Interact with buttons or rotary encoders for adjusting settings.

- **Real-time Monitoring:**  
  Integrated temperature feedback with live adjustments via temperature sensors.

- **PID Tuning:**  
  Fine-tune control loops with proportional, integral, and derivative adjustments.

---

## Getting Started

### Prerequisites
Before setting up the HOT_AIR_Station controller, ensure the following are ready:

#### Hardware
1. **Microcontroller:**  
   Supported platforms like ESP32, ESP8266, or compatible boards.
   
2. **Temperature Sensor:**  
   - Typically uses **NTC thermistors** or other temperature-sensing hardware.

3. **Motor Driver Module:**  
   - Used to adjust fan motor speed, such as L298N or other motor driver interfaces.

4. **Hot Air Blower Motor:**  
   - Controlled via PWM signals for airflow adjustments.

5. **Power Supply:**  
   - Ensure regulated and appropriate voltage to power the hot air rework station and board.

---

### Setting up the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/Afnan-Yusuf/HOT_AIR_Station.git
## Installation
1. Open the project with **PlatformIO IDE**.
2. Verify the configuration settings in `platformio.ini`.
3. Upload the firmware code to the microcontroller using the PlatformIO's upload feature.

---

## Hardware Setup & Circuit Details

### Circuit Connections
Below are the typical pin configurations necessary to interface the microcontroller with various components:

| **Component**          | **Microcontroller Pin** | **Details**               |
|-------------------------|--------------------------|---------------------------|
| Temperature Sensor      | Analog Pin (e.g., A0)   | Connected to thermistor for temperature feedback. |
| Motor Driver PWM Input  | GPIO PWM Pin (e.g., GPIO25) | PWM signal to control motor speed for airflow. |
| Hot Air Fan Motor Input | PWM Motor Terminal      | Airflow motor control. |
| UI Buttons/Rotary Encoder | GPIO 5, GPIO 6         | Allow user input for settings adjustment. |
| Motor Power Supply      | Ensure regulated voltage | Required for motor driver and air motor. |

Ensure you carefully connect and check the circuit wiring to ensure reliable performance.

---

## Running the Code
1. Upload the firmware to your development board via PlatformIO.
2. Monitor the Serial Debug Output for real-time information about temperature readings and system responses.
3. Use input controls (buttons, rotary encoder) to adjust temperature and airflow settings.

---

## Code Overview
The firmware consists of the following features:

### 1. **PID Control for Temperature**
The system implements a feedback loop using **PID (Proportional, Integral, Derivative)** control to maintain stable temperature.

#### Example:
```cpp
float Kp = 2.0; // Proportional gain
float Ki = 1.0; // Integral gain
float Kd = 1.5; // Derivative gain

