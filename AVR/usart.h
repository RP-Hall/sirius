#ifndef _USART_H
#define _USART_H

#define F_CPU 14745600UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
//#include "USART.c"

void uart1_init(void);
void usart_transmit(unsigned char data);
unsigned char usart_receive( void );


#endif