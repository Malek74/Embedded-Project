# Autonomous Vehicle Control System

This repository contains the source code, hardware designs, and documentation for an **Autonomous Vehicle Control System** developed using FreeRTOS. The project integrates various sensors and actuators to automate vehicle responses such as lane detection, obstacle avoidance, and braking, making it a foundational step toward autonomous driving technologies.

## Table of Contents
- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [Software Requirements](#software-requirements)
- [Setup Instructions](#setup-instructions)
- [Project Documentation](#project-documentation)
- [License](#license)

---

## Features
- Lane detection using an **Infrared Sensor**.
- Obstacle detection with an **Ultrasonic Sensor**.
- Vehicle acceleration and deceleration monitoring using an **MPU6050 Gyroscope**.
- Real-time display of system status via an **LCD screen**.
- Automatic brake light activation during deceleration.
- Efficient concurrency management using **FreeRTOS**.

---

## System Architecture
The system is composed of:
1. **Sensors**: Infrared, Ultrasonic, MPU6050.
2. **Actuators**: Motor, LED Brake Lights, LCD Display.
3. **Controller**: Managed using FreeRTOS for real-time task scheduling.

---

## Hardware Components
### Component List
1. **Infrared Sensor**
2. **Ultrasonic Sensor (HC-SR04)**
3. **MPU6050 Gyroscope**
4. **LEDs (Brake Lights)**: General-purpose LEDs.
5. **LCD Screen**: 16x2 character LCD.

### Connection Diagrams
Refer to the `/hardware` folder for detailed connection diagrams.

---

## Software Requirements
- **FreeRTOS Kernel**: Clone the FreeRTOS-Kernel submodule 
- **Embedded C Compiler**: (e.g., ARM GCC).
- **Microcontroller SDK**: Compatible with Raspberry Pi Pico or similar hardware.
