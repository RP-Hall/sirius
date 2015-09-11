/*
 * Dyn_test.c
 *
 * Created: 3/15/2015 11:12:32 AM
 *  Author: mukherjee
 */ 

#define F_CPU 14745600UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include "dynamixel.h"

// To be coverted into program memory
//char RESULT = SUCCESS;
int current_sending_length = MAX_SENT_PKT;
int current_receiving_length = MAX_RECV_PKT;
int status1 = 0;
int rec_index = 0;

char receive_buffer[MAX_RECV_PKT];
char send_buffer[MAX_SENT_PKT];

ISR(USART3_RX_vect)
{
	//cli();
	receive_buffer[rec_index] = UDR3;

	rec_index++;
	if(rec_index == current_receiving_length)
	{
		rec_index = 0;
		if(receive_buffer[ERROR_INDX] == SUCCESS)
		{	status1 = 1;
		//disable_recv;
		}
		else
		{	
			//lcd_cursor(1,1);
			//lcd_string("error receiving");
			lcd_cursor(2,1);
			print_receive_pkt();
		}			
		//PORTJ |= (1<<5);
		
	}
	
	//	sei();
}

void UART3_init()
{
	UCSR3A = 0x00;
	UCSR3C=(1<<UCSZ31)|(1<<UCSZ30); // 8 bit char length
	UBRR3L = 15;					// 57600 baud
	UBRR3H = 0x00;
	//UCSR3B = 0x98;
	UCSR3B=(1<<RXCIE3)|(1<<TXEN3);	// enable Rx int and Tx
}	

void buffer_init()
{
	int i;
	
	for (i=0;i<MAX_SENT_PKT;i++)
	{
		send_buffer[i] = 0;
	}
	for (i=0;i<MAX_RECV_PKT;i++)
	{
		receive_buffer[i] = 0;
	}
}

void dynamixel_init()
{
	buffer_init();
	UART3_init();
	lcd_init();
	DDRJ = (1<<5);
}

void send_pkt()
{
	int i;
	PORTJ |= (1<<5);
	disable_recv;
	for(i=0;i<current_sending_length;i++)
	{
		while ( !( UCSR3A & (1<<UDRE3)) );
		UDR3 = send_buffer[i];
	}
	_delay_us(450);//default 300 for57600 baud
	enable_recv;
	PORTJ &= ~(1<<5);
}

void print_receive_pkt()
{
	int i;
	for (i=0;i<current_receiving_length;i++)
	{
		print_hex(receive_buffer[i]);
	}
}

void print_send_pkt()
{
	int i;
	for (i=3;i<current_sending_length;i++)
	{
		print_hex(send_buffer[i]);
	}
}

char get_checksum(int index)
{
	int i;char sum = 0;
	for(i=2;i<index;i++)
		sum+=send_buffer[i];
	return ~(sum);
}

void move2pos(char id,int pos,int vel)
{
	char posL,posH,velL,velH;
	
	pos = (int)(pos*3.41) + 665;
	
	posL = pos & 0x00FF;
	posH = ((pos & 0xFF00)>>8);
	velL = vel & 0x00FF;
	velH = ((vel & 0xFF00)>>8);
	
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = id;
	send_buffer[3] = MOVE_SENT_PKT_LENGTH-4;
	send_buffer[4] = INST_WRITE;
	send_buffer[5] = GOAL_POS_ADD; 
	send_buffer[6] = posL;
	send_buffer[7] = posH;
	send_buffer[8] = velL;
	send_buffer[9] = velH;
	send_buffer[10] = get_checksum(10);
		
	current_sending_length = MOVE_SENT_PKT_LENGTH;
	current_receiving_length = MOVE_RECV_PKT_LENGTH;
	display_clear();
	print_send_pkt();
	send_pkt();
}

int current_pos(char id)
{
	int pos = -1;
	
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = id;
	send_buffer[3] = READ_SENT_PKT_LENGTH-4;
	send_buffer[4] = INST_READ;
	send_buffer[5] = 0x24; 
	send_buffer[6] = 0x02;
	send_buffer[7] = get_checksum(7);
	
	current_sending_length = READ_SENT_PKT_LENGTH;
	current_receiving_length = READ_RECV_PKT_LENGTH+1;
	
	send_pkt();
	_delay_ms(3);											// TRY TO REMOVE THIS
	//while(!(status1));
	if (receive_buffer[ERROR_INDX]==SUCCESS)	
	{	
		_delay_ms(1);
		//lcd_cursor(2,8);
		pos = ((int)(receive_buffer[6]&0x00FF)<<8)+(int)(receive_buffer[5]&0x00FF);
	
	}	
	return pos;
}

int is_moving(char id)
{
	int moving = 0;
	
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = id;
	send_buffer[3] = READ_SENT_PKT_LENGTH-4;
	send_buffer[4] = INST_READ;
	send_buffer[5] = 0x2E;
	send_buffer[6] = 0x01;
	send_buffer[7] = get_checksum(7);
	
	current_sending_length = READ_SENT_PKT_LENGTH;
	current_receiving_length = READ_RECV_PKT_LENGTH;
	
	send_pkt();
	_delay_ms(2);										// TRY TO REMOVE THIS
	//while(!(status1));
	if (receive_buffer[ERROR_INDX]==SUCCESS)
	{
		//lcd_cursor(2,8);
		if(receive_buffer[5])
			moving = 1;
	}
	return moving;
}

void wheel_mode(char id)
{	
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = id;
	send_buffer[3] = MOVE_SENT_PKT_LENGTH-4;
	send_buffer[4] = INST_WRITE;
	send_buffer[5] = 0x06;
	send_buffer[6] = 0x00;
	send_buffer[7] = 0x00;
	send_buffer[8] = 0x00;
	send_buffer[9] = 0x00;
	send_buffer[10] = get_checksum(10);
	
	current_sending_length = MOVE_SENT_PKT_LENGTH;
	current_receiving_length = MOVE_RECV_PKT_LENGTH;
	
	send_pkt();
	//_delay_us(1000);
	//wheel_mode_speed(id,0);
	//_delay_ms(1);
	
}

void wheel_mode_speed(char id,int vel)					// Vel argument -1023 to 1023 for CCW to CW rotation
{
	char velL,velH;
	
	if (vel<0)
	{
		vel = -vel;
		velH = 0x00;					// Direction bit set CCW
	}
	else
		velH = 0x04;					// Direction bit set CW
	
	velL = vel & 0x00FF;
	velH |= (vel & 0xFF00)>>8;
	
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = id;
	send_buffer[3] = MOVE_SENT_PKT_LENGTH-6;
	send_buffer[4] = INST_WRITE;
	send_buffer[5] = 0x20;				// Address for velocity
	send_buffer[6] = velL;
	send_buffer[7] = velH;
	send_buffer[8] = get_checksum(8);
	
	current_sending_length = MOVE_SENT_PKT_LENGTH-2;
	current_receiving_length = MOVE_RECV_PKT_LENGTH;
	
	//display_clear();
//	lcd_print(1,1,vel,4);
	send_pkt();
	_delay_us(650);
}

void legged_mode(char id)
{
	wheel_mode_speed(id,0);
	print_receive_pkt();
	_delay_us(650);
	
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = id;
	send_buffer[3] = MOVE_SENT_PKT_LENGTH-4;
	send_buffer[4] = INST_WRITE;
	send_buffer[5] = 0x06;
	send_buffer[6] = 0x00;
	send_buffer[7] = 0x00;
	send_buffer[8] = 0xff;
	send_buffer[9] = 0x03;
	send_buffer[10] = get_checksum(10);
	
	current_sending_length = MOVE_SENT_PKT_LENGTH;
	current_receiving_length = MOVE_RECV_PKT_LENGTH;
	
	send_pkt();
	_delay_us(650);
}

void update_pos(char id,int pos,int vel)
{
	char posL,posH,velL,velH;
	
	pos = (int)(pos*3.41)+665;
	
	posL = pos & 0x00FF;
	posH = (pos & 0xFF00)>>8;
	velL = vel & 0x00FF;
	velH = (vel & 0xFF00)>>8;
	
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = id;
	send_buffer[3] = MOVE_SENT_PKT_LENGTH-4;
	send_buffer[4] = INST_REG_WRITE;
	send_buffer[5] = GOAL_POS_ADD;
	send_buffer[6] = posL;
	send_buffer[7] = posH;
	send_buffer[8] = velL;
	send_buffer[9] = velH;
	send_buffer[10] = get_checksum(10);
	
	current_sending_length = MOVE_SENT_PKT_LENGTH;
	current_receiving_length = MOVE_RECV_PKT_LENGTH;
	
	send_pkt();
}

void wheel_mode_speed_update(char id,int vel)					// Vel argument -1023 to 1023 for CCW to CW rotation
{
	char velL,velH;
	
	if (vel<0)
	{
		vel = -vel;
		velH = 0x00;					// Direction bit set CCW
	}
	else
	{	
		velH = 0x04;					// Direction bit set CW
	}
		
	velL = vel & 0x00FF;
	velH |= (vel & 0xFF00)>>8;
	
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = id;
	send_buffer[3] = MOVE_SENT_PKT_LENGTH-6;
	send_buffer[4] = INST_REG_WRITE;
	send_buffer[5] = 0x20;				// Address for velocity
	send_buffer[6] = velL;
	send_buffer[7] = velH;
	send_buffer[8] = get_checksum(8);
	
	current_sending_length = MOVE_SENT_PKT_LENGTH-2;
	current_receiving_length = MOVE_RECV_PKT_LENGTH;
	
	//display_clear();
	//lcd_print(1,1,vel,4);
	send_pkt();
	//_delay_ms(5);
	_delay_us(650);
}

void move_dyn_sync()
{
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = 0xFE;						//broadcast id
	send_buffer[3] = 2;
	send_buffer[4] = INST_SYNC_MOVE;
	send_buffer[5] = 0xFA;
	
	current_sending_length = 6;
	current_receiving_length = 0;
	
	send_pkt();
}


void stop_wheel_mode(char id, int angle)
{
	send_buffer[0] = HEADER1;
	send_buffer[1] = HEADER2;
	send_buffer[2] = id;						//broadcast id
	send_buffer[3] = 0x05;
	send_buffer[4] = INST_REG_WRITE;
	send_buffer[5] = 0x1E;
	send_buffer[6] = (angle & 0x00FF);
	send_buffer[7] = ((angle>>8) & 0x00FF);
	
	send_buffer[8] = get_checksum(8);
	
		
	current_sending_length = 9;
	current_receiving_length = 6;
	
	send_pkt();
	_delay_ms(100);
	print_receive_pkt();
	_delay_us(1000);
	
	send_buffer[3] = 0x07;
	send_buffer[5] = 0x06;
	send_buffer[6] = 0x00;
	send_buffer[7] = 0x00;
	send_buffer[8] = 0xFF;
	send_buffer[9] = 0x03;
	
	send_buffer[10] = get_checksum(10);
	
	current_sending_length = 11;
	current_receiving_length = 6;
	
	send_pkt();
	_delay_us(650);
	print_receive_pkt();
	_delay_ms(10);
	
	
	send_buffer[3] = 2;
	send_buffer[4] = INST_SYNC_MOVE;
	
	send_buffer[5] = get_checksum(5);
	
	current_sending_length = 6;
	current_receiving_length = 6;
	
	send_pkt();
	_delay_ms(10);
	//print_receive_pkt();
}

/*

int main(void)
{
	DDRB = 0xff;PORTB = 0;int now=0;
		
	dynamixel_init();
	lcd_init();
	
	sei();
	
	
	wheel_mode(6);
	_delay_us(1000);
	
	wheel_mode_speed(6,0x0200);
	print_receive_pkt();
	_delay_ms(4000);
	
	//stop_wheel_mode(6,0x0000);
	//legged_mode(6);
	while(1)
	{
		
		
	}
	
	PORTB = 0xff;
}
*/
/*	
int main(void)
{
	DDRB = 0xff;PORTB = 0;DDRF =0xff;PORTF = 0;
	//PORTK = 0xff;
	
	cli();
	dynamixel_init();
	
	
	char data[11] = {0xFF, 0xFF, 0x06, 0x07, 0x03, 0x1E, 0x00, 0x02, 0x00, 0x02, 0xD2};
	//	char data[11] = {0xFF, 0xFF, 0x01, 0x07, 0x03, 0x1E, 0x00, 0x02, 0x00, 0x02, 0xD2};
	//char data[8] = {0xff, 0xff, 0x01, 0x04, 0x02, 0x00, 0x03, 0xf5};
	int i=0;
	char check_sum = 0;
	for (i=2;i<10;i++)
	{
		check_sum+= data[i];
	}
	data[10] = ~(check_sum & 0x00FF);
	
	
	sei();
	while(1)
	{
		
		PORTK = 0xff;
		for(i=0;i<11;i++)
		{		
			while ( !( UCSR3A & (1<<UDRE3)) );
			UDR3 = data[i];
		}
		_delay_us(100);
		current_receiving_length = 6;
		UCSR3B |=(1<<RXEN3);
		//enable_recv;
		PORTK = 0x00;
		
		while(!(status1))
		{
			PORTB = 0xff;
			_delay_ms(500);
			PORTB = 0x00;
			_delay_ms(500);
		}
		break;
	}
	print_receive_pkt();
	PORTB = 0xff;
}*/	