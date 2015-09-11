/*
 * Gait_testing.c
 *
 * Created: 04-04-2015 11:16:26
 *  Author: AMAN
 */ 

#define F_CPU 14755600ul

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include "lcd.h"
#include "dynamixel.h"
#include "roboservo.h"
#include "motion.h"
#include "config.h"

int notch_base_angle[4] = {6, 7, 10, 5};  //Only for Serial Testing
int	cut_base_angle[4] = {0, 9, 0, 0};     //Only for Serial Testing
extern data;

// int main(void)
// {
// 	_delay_ms(2000);
// 	dynamixel_init();
// 	roboservo_init();
// 	set_robo_speed();
// 	lcd_init();
// 	
// 	
// 	
// 	initial_state();
// 	_delay_ms(3000);
// 	
// 	move_bot();
//     while(1)
//     {
// 	   process_Gait(left_rotationGait);
//     }
// }

int main(void)
{
	DDRB =0xff; DDRG = 0xff;
	PORTB = 0;	PORTG = 0x00;
	char drive_flag = 0;
	dynamixel_init();
	roboservo_init();
	set_robo_speed();
	uart1_init();
	lcd_init();
	int i =0;
	_delay_ms(2000);
	
	initial_state();
	
	char state;
	
	while(1)
	{
		while(data == 0){PORTB = data;}			// wait for data receive from lcd
		
		PORTB = data;							// display received data on leds
		_delay_ms(500);
		switch(data)							// process data
		{
			case 0:
			break;
			case 'q':
				if(drive_flag)
				{dog_mode();drive_flag = 0;}
			break;
			case 'w':
				if(!drive_flag)
				{drive_mode();drive_flag =1;}
			break;//process_Gait(spiderBackward); break;
			case 'e':
				for (i=0;i<6;i++)
				{process_Gait(spiderForward);} break;
			case 'r':
				for (i=0;i<3;i++)
				{process_Gait(left_rotationGait);}break;
			case 't':
				//for (i=0;i<6;i++)
				{process_Gait(littledog_gait);} break;
			case 'y':
				//for (i=0;i<6;i++)
				{process_Gait(littledog_quasigait);} break;
			case 'u':
				drive_forward();break;
			case 'i':
				drive_reverse();break;
			case 'o':
				drive_left();break;
			case 'p':
				drive_right();break;
			case 'a':
				drive_stop();break;
			case 's':
				flash_light();break;
			case 'd':
				if(drive_flag)
				{dog_mode();drive_flag = 0;}
				process_Gait(open_studap);break;
			case 'f':
				if(drive_flag)
				{dog_mode();drive_flag = 0;}
				process_Gait(sit);break;
			case 'g':
				if(drive_flag)
				{dog_mode();drive_flag = 0;}
				process_Gait(open_transformer);break;
			case 'h':
				climb();break;		
		}
		data = 0;
// 		switch(state)
// 		{
// 			case 0:
// 					break;
// 			case 1:
// 					if(drive_flag)
// 					{dog_mode();drive_flag = 0;}
// 					break;
// 			case 2:
// 					if(!drive_flag)
// 					{drive_mode();drive_flag =1;}
// 					break;//process_Gait(spiderBackward); break;
// 			case 3:
// 					process_Gait(spiderForward); break;
// 			case 4:
// 					process_Gait(left_rotationGait);break;
// 			case 5: 
// 					process_Gait(littledog_gait); break;
// 			case 6: 
// 					process_Gait(littledog_quasigait); break;
// 			case 7:
// 					drive_forward();break;
// 			case 8:
// 					drive_reverse();break;		
// 			case 9:
// 					drive_right();break;
// 			case 10:
// 					drive_left();break;
// 			case 11:
// 					drive_stop();break;
// 			case 12:
// 					flash_light();break;
// 		}
		//state = 0;
	}
}


// function to process the packet for motion
void process_Gait (Gait gait)
{
	char i,j;
	for (i=0;i<gait.num_packets;i++)
	{
		for (j=0;j<4;j++)
		{
			update_wheel_angle(j+1,gait.packets[i].leg[j].theta[0]-90,gait.packets[i].leg[j].theta[1]-cut_base_angle[j],gait.packets[i].leg[j].theta[2]-notch_base_angle[j],gait.packets[i].leg[j].theta[3]-150);
		}
		//_delay_ms(500);
		move_bot();
	_delay_ms(500);	
	}		
}

// initial state
void initial_state()
{
	legged_mode(1);
	legged_mode(2);
	legged_mode(3);
	legged_mode(4);
	close_wheel();
	_delay_ms(2);
}

// go to drive mode
void drive_mode()
{
	go_to_base_yaw();
	close_wheel();
	wheel_mode(1);
	wheel_mode_speed(1,0);
	wheel_mode(2);
	wheel_mode_speed(2,0);
	wheel_mode(3);
	wheel_mode_speed(3,0);
	wheel_mode(4);
	wheel_mode_speed(4,0);
}

//For changing the mode of legs without moving the legs expect the yaw motors
void dog_mode()
{
	go_to_base_yaw();
	legged_mode(1);
	legged_mode(2);
	legged_mode(3);
	legged_mode(4);
//	open_wheel();
}

//For moving the bot in forward direction
void drive_forward()
{
	wheel_mode_speed_update(1,0);
	wheel_mode_speed_update(2,0);
	wheel_mode_speed_update(3,0);
	wheel_mode_speed_update(4,0);
	move_bot();
	go_to_base_yaw();
	_delay_ms(1);
	wheel_mode_speed_update(1,512);
	wheel_mode_speed_update(2,-512);
	wheel_mode_speed_update(3,-512);
	wheel_mode_speed_update(4,512);
	move_bot();
}

//For moving the bot in backward direction
void drive_reverse()
{
	wheel_mode_speed_update(1,0);
	wheel_mode_speed_update(2,0);
	wheel_mode_speed_update(3,0);
	wheel_mode_speed_update(4,0);
	move_bot();
	_delay_ms(1);
	go_to_base_yaw();
	wheel_mode_speed_update(1,-512);
	wheel_mode_speed_update(2,512);
	wheel_mode_speed_update(3,512);
	wheel_mode_speed_update(4,-512);
	move_bot();
}

//For moving the bot in right direction laterally
void drive_right()
{
	wheel_mode_speed_update(1,0);
	wheel_mode_speed_update(2,0);
	wheel_mode_speed_update(3,0);
	wheel_mode_speed_update(4,0);
	move_bot();
	_delay_ms(1);
	update_robo_angle(5,90);update_robo_angle(6,-90);update_robo_angle(7,-90);update_robo_angle(8,90);
	move_bot();
	_delay_ms(100);
	wheel_mode_speed_update(1,512);
	wheel_mode_speed_update(2,512);
	wheel_mode_speed_update(3,-512);
	wheel_mode_speed_update(4,-512);
	move_bot();
}

//For moving the bot in left direction laterally
void drive_left()
{
	wheel_mode_speed_update(1,0);
	wheel_mode_speed_update(2,0);
	wheel_mode_speed_update(3,0);
	wheel_mode_speed_update(4,0);
	move_bot();
	_delay_ms(1);
	update_robo_angle(5,90);update_robo_angle(6,-90);update_robo_angle(7,-90);update_robo_angle(8,90);move_bot();
	_delay_ms(100);
	wheel_mode_speed_update(1,-512);
	wheel_mode_speed_update(2,-512);
	wheel_mode_speed_update(3,512);
	wheel_mode_speed_update(4,512);
	move_bot();
}

//Stop in drive mode
void drive_stop()
{
	wheel_mode_speed_update(1,0);
	wheel_mode_speed_update(2,0);
	wheel_mode_speed_update(3,0);
	wheel_mode_speed_update(4,0);
	move_bot();
}

// FLASHLIGHT on port G
void flash_light()
{
	PORTG = ~PORTG;
}


// NOT TESTED
void climb()
{
	wheel_mode(3);	wheel_mode_speed(3,0);
	wheel_mode(4);  wheel_mode_speed(4,0);
	update_wheel_angle(1,89-90,0-cut_base_angle[0],0-notch_base_angle[0],238-150);
	update_wheel_angle(2,89-90,0-cut_base_angle[1],0-notch_base_angle[1],42-150);
	move_bot();_delay_ms(100);
	update_wheel_angle(1,89-90,90-cut_base_angle[0],90-notch_base_angle[0],238-150);
	update_wheel_angle(2,89-90,90-cut_base_angle[1],90-notch_base_angle[1],42-150);
	move_bot();_delay_ms(100);
	wheel_mode_speed_update(3,512);wheel_mode_speed_update(4,512);
	move_bot();
	_delay_ms(1500);
	wheel_mode_speed_update(3,0);wheel_mode_speed_update(4,0);
	move_bot();
	update_wheel_angle(2,89-90,0-cut_base_angle[0],0-notch_base_angle[0],150-150);
	update_wheel_angle(2,89-90,0-cut_base_angle[1],0-notch_base_angle[1],150-150);
	move_bot();_delay_ms(100);
	
	legged_mode(3); legged_mode(4);
	
	wheel_mode(1); wheel_mode_speed(1,0);
	wheel_mode(2); wheel_mode_speed(2,0);
	
	update_wheel_angle(3,89-90,0-cut_base_angle[2],0-notch_base_angle[2],238-150);
	update_wheel_angle(4,89-90,0-cut_base_angle[3],0-notch_base_angle[3],42-150);
	move_bot();_delay_ms(100);
	
	update_wheel_angle(3,89-90,90-cut_base_angle[2],0-notch_base_angle[2],238-150);
	update_wheel_angle(4,89-90,90-cut_base_angle[3],0-notch_base_angle[3],42-150);
	move_bot();_delay_ms(100);
	
	
}	
	