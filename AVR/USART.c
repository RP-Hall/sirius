// #include <avr/io.h>
// #include "main.h"
// #include "usart.h"


#include <avr/io.h>
#include "usart.h"
#include <util/delay.h>
#include "lcd.h"
#include "main.h"
#include "dynamixel.h"
#include "roboservo.h"
#include "motion.h"

void uart1_init(void)
{
	//DDRB = 0xff;
	//UCSR1B = 0x00; //disable while setting baud rate
	UCSR1A = 0x00;
	UCSR1C = 0x06;
	UBRR1L = 0x0F; //set baud rate lo
	UBRR1H = 0x00; //set baud rate hi
	UCSR1B = 0x98;
	//UCSR1B = (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
}

void usart_transmit(unsigned char data)
{
	while(!( UCSR1A & (1<<UDRE1) ) );
	
	UDR1 = data;
}

unsigned char usart_receive( void )
{
	while( !(UCSR1A & (1<<RXC1)) );
	
	return UDR1;
}

botPacket roboPacket;
char update_flag = 0;
//char state = 0;
char data = 0;

char flag = 0;   // Flag = 1 means valid packet being received
volatile char cntr = 0;
/*
ISR(USART1_RX_vect)
{
//cli();
  char data;
  data = UDR1;
//  PORTB = cntr;
  if ((data == 0xaa && flag == 0))
    {
      flag = 1;
      return;
    }
  if (flag == 1) 
    {

      switch(cntr)
	{
	case 0:
	  roboPacket.info_byte = data;   // Leg Id to be sent as 0, 1, 2, 3 Corresponding to leg 1, 2, 3, 4
	  //PORTB = roboPacket.info_byte;
	  break;
	case 1:
	  roboPacket.my_Robo.leg[0].theta[0] = data;
	  break;
	case 2:
	  roboPacket.my_Robo.leg[0].theta[1] = data;
	  break;
	case 3:
	  roboPacket.my_Robo.leg[0].theta[2] = data;
	  break;
	case 4:
	  roboPacket.my_Robo.leg[0].theta[3] = data;
	  break;
	case 5:
	  roboPacket.my_Robo.leg[1].theta[0] = data;
	  break;
	case 6:
	  roboPacket.my_Robo.leg[1].theta[1] = data;
	  break;
	case 7:
	  roboPacket.my_Robo.leg[1].theta[2] = data;
	  break;
	case 8:
	  roboPacket.my_Robo.leg[1].theta[3] = data;
	  break;
	case 9:
	  roboPacket.my_Robo.leg[2].theta[0] = data;
	  break;
	case 10:
	  roboPacket.my_Robo.leg[2].theta[1] = data;
	  break;
	case 11:
	  roboPacket.my_Robo.leg[2].theta[2] = data;
	  break;
	case 12:
	  roboPacket.my_Robo.leg[2].theta[3] = data;
	  break;
	case 13:
	  roboPacket.my_Robo.leg[3].theta[0] = data;
	  break;
	case 14:
	  roboPacket.my_Robo.leg[3].theta[1] = data;
	  break;
	case 15:
	  roboPacket.my_Robo.leg[3].theta[2] = data;
	  break;
	case 16:
	  flag = 0;
	  update_flag = 1;
	  //PORTB = update_flag;
	  cntr = -1;
	  roboPacket.my_Robo.leg[3].theta[3] = data;
	  break;
	}
      cntr++;
    }
}
*/
ISR(USART1_RX_vect)
{
	//cli();
	data = UDR1;
	//  PORTB = cntr;
	/*switch(data)
	{
		case 'q': 
				state = 1;break;					// Walk mode
		case 'w': 
				state = 2;break;					// Drive mode
		case 'e': 
				state = 3;break;					// Spider	
		case 'r':		
				state =	4;break;					// Rotation
		case 't': 
				state = 5;break;					// Static
		case 'y': 
				state = 6;break;					// Quasi
		case 'u':
				state = 7;break;					// Forward
		case 'i':
				state = 8;break;					// Reverse
		case 'o':
				state = 9;break;					// Right
		case 'p':
				state = 10;break;					// Left
		case 'a':
				state = 11;break;					// Stop
		case 's':
				state = 12;break;					// Flash Light
		case 'd':
				state = 13;break;
		case 'f':
				state = 14;break;
		default: break;
		
	}*/
	
	usart_transmit(data);

}







	  
	      
	
  
