# Laptop-Controlled Targeting Vehicle (with Camera Feed)

This repository contains the code and resources for the laptop control system that allows remote control of the Bluetooth-controlled targeting vehicle. The laptop connects to the car's camera to provide a live feed of the arena, enabling the user to control the vehicle from a distance, navigate to targets, and engage in the shooting task. It also has a debugging terminal used to test out responsiveness of the vehicle.

## Key Features:
- **Live Camera Feed:** The laptop receives a real-time video feed from the car's camera, enabling the user to visually navigate the arena and control the vehicle remotely.
- **TCP/IP Communication:** The laptop communicates with the car over a TCP/IP connection to send control commands (e.g., motor movements, turret adjustments, etc.).
- **Debugging Interface:** The laptop interface includes debugging functionalities that allow the user to test various actions like turning, rotating, and firing, as well as monitoring vehicle feedback (e.g., motor status, sensor readings).
