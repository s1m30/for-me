# Obstacle Avoiding Robot Car (World Robotics Olympiad Future Engineers Category)

![Obstacle Avoiding Robot Car](https://github.com/user-attachments/assets/1a5e6c07-c0ee-4770-b8bc-c13171de9587)
![Obstacle Avoiding Robot Components](https://github.com/user-attachments/assets/664d53f1-93e0-479b-b262-7a2ad9abfbf7)

This repository is dedicated to the **6th Touch Team Future Engineers** project for the World Robotics Olympiad. The project is an obstacle-avoiding robot that uses sensors to navigate through its surroundings. The primary source code is **Carmotor.ino**, while the remaining code files are for individually testing out the main components of the car (motors, ultrasonic sensors, and servomotor).

## Components Used
- **L298N Motor Driver** x1
- **Ultrasonic Sensors HC-SR04** x4
- **Car Chassis** x1
- **Arduino Uno/Nano**
- **Jumper Wires** (male-to-male, male-to-female, and female-to-male) x as needed
- **Batteries** (Recommended: two separate battery modules; high-power lithium batteries for the motor driver and a 9V battery for Arduino)
- **Color Sensor** x1 (Note: not implemented in the main code)

## About the Code
The code is written entirely in C++ using the Arduino IDE. It includes functions for:
- Changing direction and turning (forward, backward, left, and right)
- Adjusting turning using PWM
- Handling obstacles based on sensor readings
- Recording readings from ultrasonic sensors

The main loop is divided into three parts:
1. **doScans**: Responsible for recording readings from the ultrasonic sensors.
2. **handleObstacles**: Processes these readings to avoid obstacles.
3. **moveForward**: Commands the car to move forward.

## Similar Projects
For more inspiration, check out these similar projects:
- [Autonomous RC Car on Instructables](https://www.instructables.com/Autonomous-RC-Car/)
- [Multi-Functional 2WD Driving Straight Robot Car](https://www.hackster.io/Kenan-Paralija/multi-functional-2wd-driving-straight-robot-car-f2e)
- [How to Make a Robot Car Drive Straight and Turn](https://www.instructables.com/How-to-Make-a-Robot-Car-Drive-Straight-and-Turn-Ex/)
- [Making a 2WD Arduino Vehicle Drive Straight](https://www.hackster.io/Kenan-Paralija/making-a-2wd-arduino-vehicle-drive-straight-ae40ee)
- [Digital Town Project 2 Robot Car](http://digitaltown.co.uk/project2RobotCar.php)
