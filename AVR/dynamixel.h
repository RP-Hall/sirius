#ifndef _DYNAMIXEL_H
#define _DYNAMIXEL_H

#define F_CPU 14745600UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"

#define HEADER1 0xFF
#define HEADER2 0xFF
#define INST_READ 0x02						// Read instruction
#define INST_WRITE 0x03						// Write Instruction
#define INST_REG_WRITE 0x04
#define INST_SYNC_MOVE 0x05
#define MAX_SENT_PKT 11						// for initializing global sending buffer
#define MAX_RECV_PKT 7						// for initialising global receiving buffer
#define MOVE_SENT_PKT_LENGTH 11
#define MOVE_RECV_PKT_LENGTH 6
#define READ_SENT_PKT_LENGTH 8
#define READ_RECV_PKT_LENGTH 7				// 
#define GOAL_POS_ADD 0x1E
#define CONTROL_PORT DDRK
#define CONTROL_PIN PORTK

#define SUCCESS 0x00
#define ERROR_INDX 4

#define enable_recv UCSR3B |=(1<<RXEN3)		// enable Rx
#define disable_recv UCSR3B &=~(1<<RXEN3)	// disable Rx


/*

	IDs:
	1 |________| 2
	  |		   |
	  |		   |
	  |        |
	  |        |
	  |________|
	3 |		   | 4

*/
ISR(USART3_RX_vect);
// Iterrupt Service Routine used for reading whenever 
// data is received

void UART3_init();
// Initailizes the UART communication with predefined
// baud 57600, with which dynamixel works better

void buffer_init();
// Initializing the buffer used for reading
// Response from Dynamixel may vary in size

void dynamixel_init();
// Initializing the (1)buffer (2)uart (3)LCD
// PORTK pin is used as data direction control 

void send_pkt();
// Sends the data stored in send_buffer[]

void print_receive_pkt();
// Prints the received data on LCD

void print_send_pkt();
// Prints the package being sent

char get_checksum(int index);
// Helper function for calculating checksum 
// Returns the checksum

void move2pos(char id,int pos,int vel);
// Function to run the wheel
// id: ID of the motor
// pos: Angle between 0-300 degrees
// vel: Velocity

int current_pos(char id);
// Retunrs current position of motor with given ID

int is_moving(char id);
// Returns 1 if motor with ID is running

void wheel_mode(char id);
// Runs motor as a normal motor
// Continuous rotation

void wheel_mode_speed(char id,int vel);
// Speed for wheel mode

void legged_mode(char id);
// Non-continuous mode
// Motor will rotate when angle is sent

void update_pos(char id,int pos,int vel);
// Used for sync running, stores position in Dynamixel

void wheel_mode_speed_update(char id,int vel);
// Used for sync running, stores velocity in Dynamixel

void move_dyn_sync();
// Runs the Dynamixel simultaneously. Angles are set in update_pos(char, int, int)

void stop_wheel_mode(char id, int angle);

#endif