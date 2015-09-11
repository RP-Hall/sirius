/* Robot Motor Configuration

			Front Side from Top(wheel Number)
			
				6			4
			
			    1			2
				
			Front Side from top(Servo ID)                 
			
		30deg->		1(2)			4(1)		  			
		150deg->	2				3	
		Top			5				6
				
		30deg->		11(3)			10(4)
		150deg->	12				9
		TOP			7				8		

*/
#define F_CPU 14745600UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include "motion.h"
#include "lcd.h"
#include "roboservo.h"
#include "dynamixel.h"


// Move all the motors to destination together
void move_bot()
{
	send_robo_packet();				
	move_dyn_sync();
}

// move legs to safe position(closed)
void go_to_safe_angle()
{
	update_wheel_angle(1,BASE_ANGLE_YAW6,SAFE_ANGLE,SAFE_ANGLE, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,SAFE_ANGLE,SAFE_ANGLE, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,SAFE_ANGLE,SAFE_ANGLE, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,SAFE_ANGLE,SAFE_ANGLE, 0);
}

// move to base angle for yaw motors i.e. facing straight
void go_to_base_yaw()
{
	update_robo_angle(5,BASE_ANGLE_YAW5);
	update_robo_angle(6,BASE_ANGLE_YAW6);
	update_robo_angle(7,BASE_ANGLE_YAW7);
	update_robo_angle(8,BASE_ANGLE_YAW8);
	send_robo_packet();
}

// move dynamixels to uprght position
void go_to_base_dynamixel()
{
	move2pos(1,0,512);
	move2pos(2,0,512);
	move2pos(3,0,512);
	move2pos(4,0,512);
}

// move motors in quarter with cut to their base angle
void go_to_base_cut()
{
	update_robo_angle(1,BASE_ANGLE_CUT1);
	update_robo_angle(3,BASE_ANGLE_CUT3);
	update_robo_angle(9,BASE_ANGLE_CUT9);
	update_robo_angle(11,BASE_ANGLE_CUT11);
}

// move motors in quarter with notch to their base angle
void go_to_base_notch()
{
	update_robo_angle(2,BASE_ANGLE_NOTCH2);
	update_robo_angle(4,BASE_ANGLE_NOTCH4);
	update_robo_angle(10,BASE_ANGLE_NOTCH10);
	update_robo_angle(12,BASE_ANGLE_NOTCH12);
}

// move the leg to desired position
void move_wheel_angle(char id_leg,int yaw, int cut_angle, int notch_angle)
{
	switch (id_leg){
		case 2:
		update_robo_angle(2,notch_angle);	update_robo_angle(1,cut_angle);	update_robo_angle(5,yaw);
		send_robo_packet(12);break;
		case 1:
		update_robo_angle(4,notch_angle);	update_robo_angle(3,cut_angle);	update_robo_angle(6,yaw);
		send_robo_packet(12);break;
		case 3:
		update_robo_angle(10,notch_angle);	update_robo_angle(9,cut_angle); update_robo_angle(8,yaw);
		send_robo_packet(12);break;
		case 4:
		update_robo_angle(12,notch_angle);	update_robo_angle(11,cut_angle); update_robo_angle(7,yaw);
		send_robo_packet(12);break;
	}
}


// update the destination position of legs to be moved in sync later
void update_wheel_angle(char id_leg,int yaw, int cut_angle, int notch_angle,int dyn_angle)
{
	switch (id_leg){
		case 2:
		update_robo_angle(2,notch_angle);	update_robo_angle(1,cut_angle);	update_robo_angle(5,yaw); update_pos(id_leg, dyn_angle, 512);
		break;
		case 1:
		update_robo_angle(4,notch_angle);	update_robo_angle(3,cut_angle);	update_robo_angle(6,yaw);update_pos(id_leg,dyn_angle, 512);
		break;
		case 3:
		update_robo_angle(10,notch_angle);	update_robo_angle(9,cut_angle); update_robo_angle(7,yaw);update_pos(id_leg,dyn_angle, 512);
		break;
		case 4:
		update_robo_angle(12,notch_angle);	update_robo_angle(11,cut_angle); update_robo_angle(8,yaw);update_pos(id_leg,dyn_angle, 512);
		break;
	}
}

// sequence for going to leg mode and standing
void open_wheel()
{
	go_to_base_dynamixel();
	update_wheel_angle(1,BASE_ANGLE_YAW6,BASE_ANGLE_CUT3,BASE_ANGLE_NOTCH4, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,BASE_ANGLE_CUT1,BASE_ANGLE_NOTCH2, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,BASE_ANGLE_CUT9,BASE_ANGLE_NOTCH10, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,BASE_ANGLE_CUT11,BASE_ANGLE_NOTCH12, 0);
	send_robo_packet();_delay_ms(1000);
	update_wheel_angle(1,BASE_ANGLE_YAW6,BASE_ANGLE_CUT3,30, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,BASE_ANGLE_CUT1,30, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,BASE_ANGLE_CUT9,30, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,BASE_ANGLE_CUT11,30, 0);
	send_robo_packet();_delay_ms(1000);
	update_wheel_angle(1,BASE_ANGLE_YAW6,30,45, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,30,45, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,30,45, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,30,45, 0);
	send_robo_packet();_delay_ms(1000);
	update_wheel_angle(1,BASE_ANGLE_YAW6,60,45, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,60,45, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,60,45, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,60,45, 0);
	send_robo_packet();_delay_ms(1000);
	update_wheel_angle(1,BASE_ANGLE_YAW6,85,60, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,85,60, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,85,60, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,85,60, 0);
	send_robo_packet();_delay_ms(1000);
	update_wheel_angle(1,BASE_ANGLE_YAW6,85,70, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,85,70, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,85,70, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,85,70, 0);
	send_robo_packet();_delay_ms(1000);
	
}


// sequence for closing the legs
void close_wheel()
{
	go_to_base_dynamixel();
	update_wheel_angle(1,BASE_ANGLE_YAW6,85,70, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,85,70, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,85,70, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,85,70, 0);
	send_robo_packet();_delay_ms(500);/*
	update_wheel_angle(1,BASE_ANGLE_YAW6,85,60);
	update_wheel_angle(2,BASE_ANGLE_YAW5,85,60);
	update_wheel_angle(3,BASE_ANGLE_YAW7,85,60);
	update_wheel_angle(4,BASE_ANGLE_YAW8,85,60);
	send_robo_packet();_delay_ms(500);*/
	update_wheel_angle(1,BASE_ANGLE_YAW6,60,45, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,60,45, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,60,45, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,60,45, 0);
	send_robo_packet();_delay_ms(500);/*
	update_wheel_angle(1,BASE_ANGLE_YAW6,30,45);
	update_wheel_angle(2,BASE_ANGLE_YAW5,30,45);
	update_wheel_angle(3,BASE_ANGLE_YAW7,30,45);
	update_wheel_angle(4,BASE_ANGLE_YAW8,30,45);
	send_robo_packet();_delay_ms(500);
	update_wheel_angle(1,BASE_ANGLE_YAW6,BASE_ANGLE_CUT3,30);
	update_wheel_angle(2,BASE_ANGLE_YAW5,BASE_ANGLE_CUT1,30);
	update_wheel_angle(3,BASE_ANGLE_YAW7,BASE_ANGLE_CUT9,30);
	update_wheel_angle(4,BASE_ANGLE_YAW8,BASE_ANGLE_CUT11,30);
	send_robo_packet();_delay_ms(500);*/
	update_wheel_angle(1,BASE_ANGLE_YAW6,BASE_ANGLE_CUT3,BASE_ANGLE_NOTCH4, 0);
	update_wheel_angle(2,BASE_ANGLE_YAW5,BASE_ANGLE_CUT1,BASE_ANGLE_NOTCH2, 0);
	update_wheel_angle(3,BASE_ANGLE_YAW7,BASE_ANGLE_CUT9,BASE_ANGLE_NOTCH10, 0);
	update_wheel_angle(4,BASE_ANGLE_YAW8,BASE_ANGLE_CUT11,BASE_ANGLE_NOTCH12, 0);
	send_robo_packet();_delay_ms(500);
}

