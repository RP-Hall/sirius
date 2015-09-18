	Circuit:	Schematics for embedded sub-systems
		All files (except ckts.jpg) are opened with 'Proteus' software
		ckts.jpg: Snapshot of schematic
		powerSirius.pdsprj: Proteus files for schematics

		Schematic contents: 
			1. Servo power system (Left)
			2. Robokits 16-Servo Motor Controller (Right Top)
			3. Communication System for Dynamixel (Right Bottom)

	AVR: Contains codes for AtMEGA2560, Board used: AtMEGA2560 development 		board by 'Nex Robotics'
		Gait_Testing.c: File for testing gaits and debugging
		USART.c:	Functions for serial communication
		usart.h: 	Header for USART.c
		config.c:	Contains configurations for all gaits
		config.h: 	Header for config.c
		dynamixel.c:	Files for running Dynamixels
		dynamixel.h: 	Header for dynamixel.c
		lcd.c:	Files for showing output on LCD (connected at PORTD)	
		lcd.h:	Header for lcd.c
		main.h: For running main process (different gaits)
		motion.c:	Files for motion of legs
		motion.h: 	Header for motion.c
		roboservo.c:	File for running servo motors
		roboservo.h: 	Header for roboservo.c

	Gaits: Angles for servos for different gaits
		backspider:	Spider gait backwards
		home:	Default gait
		littledog_gait:	Dog gait
		little_gait_quasi:	Quasi dog gait
		roll_gait:	Wheel gait
		rotation_gait:	Rotation
		spiderwalk:	Spider gait

	MATLAB: 
		matlab_camera:
			camera.asv:
			camera.m
			final_image.jpg:
			imageConvert.py:
			image_raw.txt:
			out_image.jpg:
			rawtoimage.m:

		matlab_inverse_kinematics:
			acceptable_angles.txt:
			angle_conversion_even.m:
			angle_conversion_odd:
			gait.m:
			inversekinematics.m
			packet_angles.txt
			packet_generation.m:

	Serial_Testing: For testing serial ports 
		main.cpp:	main process
		serial.cpp:	contains serial function
		serial.h:	header for serial.c



