# SIRIUS - A Wheel-Leg Transfigurable Robot


## Video

[![Sirius Video](http://img.youtube.com/vi/tceGkQNUUpM/0.jpg)](https://youtu.be/tceGkQNUUpM)



## Circuitry

All schematics for embedded sub-systems are opened with 'Proteus' software

![Sirius Circuitry](https://upload.wikimedia.org/wikipedia/commons/8/87/Sirius-ckt.JPG)

File: powerSirius.pdsprj: Proteus files for schematics

Schematic contents:  
1. Servo power system (Left)  
2. Robokits 16-Servo Motor Controller (Right Top)  
3. Communication System for Dynamixel (Right Bottom)


## File Explorer

Controller:  AtMEGA2560
Board used: [AtMEGA2560 Development Board](http://www.nex-robotics.com/products/microcontroller-development-boards/atmega2560-development-board.html)

###AVR
* Gait_Testing.c: File for testing gaits and debugging
* USART.c:	Functions for serial communication
* usart.h: 	Header for USART.c
* config.c:	Contains configurations for all gaits
* config.h: 	Header for config.c
* dynamixel.h dynamixel.c:	Files for running Dynamixels
* lcd.h lcd.c:	Files for showing output on LCD (connected at PORTD)	
* main.h: For running main process (different gaits)
* motion.h motion.c:	Files for motion of legs
* roboservo.h roboservo.c:	File for running servo motors

###Gaits
* backspider: Spider gait backwards
* home:	Home orientations
* littledog_gait: Dog gait
* little_gait_quasi: Quasi dog gait
* roll_gait: Wheel gait
* rotation_gait: Rotation
* spiderwalk: Spider gait

###MATLAB

* matlab_camera:
	** camera.m: Gets camera feed
	** imageConvert.py: Convert binary format image to jpeg
	** image_raw.txt: Raw image text file through camera
	** out_image.jpg: Output image
	** rawtoimage.m: MATLAB function to convert binary to image jpg

* matlab_inverse_kinematics:
	** acceptable_angles.txt: Text File to store acceptable angles after Gait Generation
	** angle_conversion_even.m: Convert Angles according to contraints for even angles
	** angle_conversion_odd: Convert Angles according to contraints for even angles
	** gait.m: File to calculate possible gaits
	** inversekinematics.m: Solves inverse kinematic equations
	** packet_angles.txt: Stores the angles to be sent as packet via serial
	** packet_generation.m: Generates packet format text file to be sent

###Serial_Testing
C++ Code for sending angles via serial communication.
* main.cpp:	main process
* serial.h serial.cpp: Serial Implementation



##Mechanical Design
