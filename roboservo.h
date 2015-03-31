//#define F_CPU 14745600ul

#include <avr/io.h>
#include <util/delay.h>

#ifndef _roboservo_H
#define _roboservo_H

void USARTInit2();
//void send_packet();
void send_robo_packet();
void update_robo_angle(char id, int angle);
void connect_controller();
void roboservo_init();
// void open_leg();
// void close_leg();
void update_packet(char lsb1,char msb1,char lsb2,char msb2,char lsb3,char msb3,char lsb4,char msb4,char lsb5,char msb5,char lsb6,char msb6,char lsb7,char msb7,char lsb8,char msb8);
void top_servo(char id, int angle);   //id is from 1 to 4;
//int mapping(char id);

#endif