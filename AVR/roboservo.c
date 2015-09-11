/*
 * robo_test.c
 *
 * Created: 24-03-2015 23:09:57
 *  Author: AMAN
 */ 



#define F_CPU 14745600U
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include "roboservo.h"

//index of robo_packet is servo_id
char robo_packet[] = {170 , 10, 76, 8, 92, 29, 80, 29, 80, 7, 88,15,  88,15,  88,15,  88,15, 4, 28, 64, 6, 124, 7, 112, 28, 100, 16, 100, 16, 100, 16, 100, 16};
char yaw_speed = 96;
char dual_speed = 72;

void USARTInit2()
{
	UBRR2L = 7;
	UBRR2H = 0x00;

	UCSR2C=(1<<UCSZ21)|(1<<UCSZ20);
	UCSR2B=(1<<TXEN2);
	sei();
}

// set speed for robokits motors
void set_robo_speed()
{
	char count;
	for (count =1;count<17;count++)
	{
		while ( !( UCSR2A & (1<<UDRE2)) );	UDR2 = 170;
		while ( !( UCSR2A & (1<<UDRE2)) );	UDR2 = 8;
		while ( !( UCSR2A & (1<<UDRE2)) );	UDR2 = count-1;
		
		if (count>=5 && count <=8)
		{
			while ( !( UCSR2A & (1<<UDRE2)) );	UDR2 = 127-yaw_speed;
		}
		else
		{
			while ( !( UCSR2A & (1<<UDRE2)) );	UDR2 = 127-dual_speed;	
		}
	}
}

// send the comm. packet to servo controller for robokits motors
void send_robo_packet()
{
	//id = mapping(id);    //use when mapping is required
	int i=0;
	for (i=0;i<34;i++)
	{
	//	_delay_ms(2);
		while ( !( UCSR2A & (1<<UDRE2)) );
		UDR2 = robo_packet[i];
	}
}

// void open_leg()
// {
// 	int open_delay = 500;
// 	update_packet(76, 8, 92, 29, 80, 29, 80, 7, /*100, 16, 100, 16, 100, 16, 100, 16,*/ 4, 28, 64, 6, 124, 7, 112, 28);
// 	_delay_ms(open_delay);
// 	update_packet(76, 8, 52, 20, 88, 28, 16, 16, /*100, 16, 100, 16, 100, 16, 100, 16,*/ 4, 28, 80, 16, 124, 7, 116, 17);
// 	_delay_ms(open_delay);
// 	update_packet(84, 14, 52, 20, 72, 21, 16, 16, /*100, 16, 100, 16, 100, 16, 100, 16,*/ 48, 21, 80, 16, 16, 13, 116, 17);
// 	_delay_ms(open_delay);
// 	update_packet(48, 20, 52, 20, 120, 14, 16, 16,/* 100, 16, 100, 16, 100, 16, 100, 16,*/ 124, 15, 80, 16, 60, 18, 116, 17);
// 	_delay_ms(open_delay);
// 	update_packet(48, 20, 36, 12, 120, 14, 88, 22, /*100, 16, 100, 16, 100, 16, 100, 16,*/ 124, 15, 36, 24, 60, 18, 120, 10);
// 	_delay_ms(open_delay);
// }

// void close_leg()
// {
// 	int close_delay = 500;
// 	update_packet(48, 20, 36, 12, 120, 14, 88, 22, /*100, 16, 100, 16, 100, 16, 100, 16, */124, 15, 36, 24, 60, 18, 120, 10);
// 	_delay_ms(close_delay);
// 	update_packet(48, 20, 52, 20, 120, 14, 16, 16,/* 100, 16, 100, 16, 100, 16, 100, 16,*/ 124, 15, 80, 16, 60, 18, 116, 17);
// 	_delay_ms(close_delay);
// 	update_packet(84, 14, 52, 20, 72, 21, 16, 16, /*100, 16, 100, 16, 100, 16, 100, 16,*/ 48, 21, 80, 16, 16, 13, 116, 17);
// 	_delay_ms(close_delay);
// 	update_packet(76, 8, 52, 20, 88, 28, 16, 16,/* 100, 16, 100, 16, 100, 16, 100, 16,*/ 4, 28, 80, 16, 124, 7, 116, 17);
// 	_delay_ms(close_delay);
// 	update_packet(76, 8, 92, 29, 80, 29, 80, 7, /*100, 16, 100, 16, 100, 16, 100, 16,*/ 4, 28, 64, 6, 124, 7, 112, 28);
// 	_delay_ms(close_delay);
// }
/*
void update_packet_id(char id, char lsb, char msb)
{
	robo_packet[2*id] = lsb;
	robo_packet[2*id+1] = msb;
}*/

void update_packet(char lsb1,char msb1,char lsb2,char msb2,char lsb3,char msb3,char lsb4,char msb4,/*char lsb5,char msb5,char lsb6,char msb6,char lsb7,char msb7,char lsb8,char msb8,*/char lsb9,char msb9,char lsb10,char msb10,char lsb11,char msb11,char lsb12,char msb12)
{
	robo_packet[2] = lsb1;
	robo_packet[3] = msb1;
	robo_packet[4] = lsb2;
	robo_packet[5] = msb2;
	robo_packet[6] = lsb3;
	robo_packet[7] = msb3;
	robo_packet[8] = lsb4;
	robo_packet[9] = msb4;
	robo_packet[10] = 88;
	robo_packet[11] = 15;
	robo_packet[12] = 88;
	robo_packet[13] = 15;
	robo_packet[14] = 88;
	robo_packet[15] = 15;
	robo_packet[16] = 88;
	robo_packet[17] = 15;
	robo_packet[18] = lsb9;
	robo_packet[19] = msb9;
	robo_packet[20] = lsb10;
	robo_packet[21] = msb10;
	robo_packet[22] = lsb11;
	robo_packet[23] = msb11;
	robo_packet[24] = lsb12;
	robo_packet[25] = msb12;
	send_robo_packet(12);
}
/*
// angle to be supplied in zero to 180 
void update_robo_angle3(char id,int angle)
{
	int data = 0;
	//data = 1912 + (int)(44.4*(float)(angle-30));
	data = (int)(43.58*(float)(angle))+604;
	
	robo_packet[2*id] = data & 0x00FF;
	robo_packet[2*id+1] = (data & 0xFF00)>>8;
	print_hex(robo_packet[2*id]);
	print_hex(robo_packet[2*id+1]);
	send_robo_packet(id);
}


// angle to be supplied according to UI : scaled up from 0 to 7000
void update_robo_angle2(char id,int angle)
{
	robo_packet[2*id] = angle & 0x00FF;
	robo_packet[2*id+1] = (angle & 0xFF00)>>8;
	display_clear();
	print_hex(robo_packet[2*id+1]);
	print_hex(robo_packet[2*id]);
	send_robo_packet(id);
}
*/


//to be used
// update angle for robokit motors with id
void update_robo_angle(char id, int angle)
{
	int data;
	if (id == 1 || id==4 || id == 10 || id==11)
	{
		angle = angle + 30;
	}
	else if (id == 2 || id ==3 || id == 9 || id == 12 )
	{
		angle = 150 - angle;
	}
	else if (id >=5 || id<=8)
	{
		angle = angle + 90;
	}
	
	//lcd_print(1,1,angle,3);
	data = 21*angle + 460;
	robo_packet[2*id] = data & 0x7F; //lower 7 bit
	robo_packet[2*id+1] = (data>>7) & 0xFF;
	//display_clear();	
	//print_hex(robo_packet[2*id+1]);
	//print_hex(robo_packet[2*id]);
	//send_robo_packet(id);
}

void top_servo(char id, int angle)   //id is from 1 to 4, angle from 0 to 180, initial position at 90;
{
	int data;
	data = 21*angle + 460;
	robo_packet[2*id+10] = data & 0x7F; //lower 7 bit
	robo_packet[2*id+11] = (data>>7) & 0xFF;
}


// to connect the servo controller to Atmega proccessor for setting up communication.
void connect_controller()
{
	unsigned int i=0;
	//for(i=0; i<5; i++){
		
		// can work if we send this only once 
		while(i<10){
			_delay_ms(1);
			while ( !( UCSR2A & (1<<UDRE2)) );
			UDR2 = 0x2E; // anything other that dot  -- dot (.) 
			_delay_ms(1);
			while ( !( UCSR2A & (1<<UDRE2)) );
			UDR2 = 0x43; // C ('C' to start the sequence in servo controller)
			i++;
	}
}

// init function for servo controller
void roboservo_init()
{
	USARTInit2();
	connect_controller();
}
