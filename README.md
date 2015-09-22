# SIRIUS - A Wheel-Leg Transfigurable Robot

![Sirius](https://upload.wikimedia.org/wikipedia/commons/b/bc/Sirius-robot.jpg)


## Video

[![Sirius Video](http://img.youtube.com/vi/tceGkQNUUpM/0.jpg)](https://youtu.be/tceGkQNUUpM)

##Presentation
[![Sirius Presentation](https://upload.wikimedia.org/wikipedia/commons/7/7e/Sirius-ppt.png)](http://www.slideshare.net/soumyadeepmukherjee17/hm2015-52970964)

##System Design

The following picture describe the system design of the robot:

![Overall-Architecture](https://upload.wikimedia.org/wikipedia/commons/0/01/Flowchart_detailed.png)

The following picture describes the control inputs to the robot:

![Control-Architecture](https://upload.wikimedia.org/wikipedia/commons/9/9d/Lcd-architecture.png)


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
	* acceptable_angles.txt: Text File to store acceptable angles after Gait Generation
	* angle_conversion_even.m: Convert Angles according to contraints for even angles
	* angle_conversion_odd: Convert Angles according to contraints for even angles
	* gait.m: File to calculate possible gaits
	* inversekinematics.m: Solves inverse kinematic equations
	* packet_angles.txt: Stores the angles to be sent as packet via serial
	* packet_generation.m: Generates packet format text file to be sent

###Serial_Testing
C++ Code for sending angles via serial communication.
* main.cpp:	main process
* serial.h serial.cpp: Serial Implementation


##Mechanical Design
All Solidworks Parts are uploaded.

![Sirius Mechanical Design](https://upload.wikimedia.org/wikipedia/commons/8/82/MechD-sirius.jpg)

![Sirius Wheel Design](https://upload.wikimedia.org/wikipedia/commons/6/6e/WheelSirius.jpg)

##References

[1] Kenjiro TADAKUMA(Osaka Univ.) et. al, Mechanical Design of the Wheel-Leg Hybrid Mobile Robot to Realize a Large Wheel Diameter. IEEE/RSJ International Conference on Intelligent Robots and Systems, Taipei, Taiwan, 2010  
[2] Carlos Queiroz, Nuno Gon ?calves and Paulo Menezes, A study on Static Gaits for a Four Leg Robot, CONTROL 2000, International Conference on, At Cambridge, UK  
[3] Nils Brynedal Ignell,Niclas Rasmusson and Johan Matsson, An overview of legged and wheeled robotic locomotion. IRCSE ’12. IDT Mini-conference on Interesting Results in Computer Science and Engineering, Sweden, 2012  
[4] Raibert, M. H. Legged Robots Communications of the ACM 499, June 1986 Volume 29 Number 6 http://www.universelle-automation.de/1980 Boston.pdf  
[5] Buckley D. 2011 http://davidbuckley.net/DB/HistoryMakers.htm  
[6] Arikawa, K., Hirose, S., 2007 Mechanical design of walking machines Philosophical Transactions of the Royal Society A 365  
[7] Heikkil,M.,Pietikinen,M.andSchmid,C.(2009),DescriptionofInter- est Regions with Local Binary Patterns. Pattern Recognition 42(3):425-436.  
[8] Christian Weiss,Nikolas Fechner,Matthias Stark and Andreas Zell,Comparison of Different Approaches to Vibration-based Terrain Clas- sification, ECMR07  


##Team
* Captains
	* Aditya Tiwari
	* Diwakar Paliwal
	* Vinay Varma
	* Sai Prasad Arkal
* Rest
	* Keshav Sarraf
	* Soumyadeep Mukherjee
	* Rishal Raj
	* Vishnu Sharma
	* Aman Gupta
	* Nipurn Gulgulia
	* Raushan Kumar
	* Kawaljeet Kumar
	* Divya Prakash
	* Seemant Jay
	* Rahul Singh
	* Kumar Abhinav