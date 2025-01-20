# Bluetooth-Controlled Targeting Vehicle

This repository contains the code and resources for the Bluetooth-controlled targeting vehicle. The vehicle is designed to navigate an arena, identify targets marked with QR codes, and shoot them autonomously or manually. 

## Key Features:
- **Autonomous Navigation:** The car uses a camera to detect QR codes and calculates the distance to targets based on their size. It follows a predetermined path to navigate through the arena and reach each target.
- **Manual Control:** Initially, the car was controlled via TCP/IP communication with a laptop, later adapted to be controlled by a PS4 controller for real-time manual operation.
- **Targeting System:** The car's turret is aimed and fired using calculated distances from QR codes, ensuring precise shots at the targets.
  
## Technologies Used:
- Raspberry Pi
- C++
- OpenCV (for QR code detection)
- SolidWorks (for chassis design)
- KiCad (for custom PCB design)
- TCP/IP Communication
- Servos for movement and turret control
