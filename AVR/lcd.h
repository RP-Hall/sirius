//#define F_CPU 14745600UL

#include <avr/io.h>
#include <util/delay.h>

#ifndef _LCD_H
#define _LCD_H

#define RS 0
#define RW 1
#define EN 2
#define lcd_port PORTC


#define sbit(reg,bit)	reg |= (1<<bit)			// Macro defined for Setting a bit of any register.
#define cbit(reg,bit)	reg &= ~(1<<bit)		// Macro defined for Clearing a bit of any register.

void lcd_port_config();
void lcd_reset();
void lcd_init();
void lcd_set_4bit();
void lcd_wr_command(unsigned char);
void lcd_wr_char(char);
void lcd_line1();
void lcd_line2();
void lcd_string(char*);
void display_clear(void);
void lcd_print (char row, char coloumn, unsigned int value, int digits);
void lcd_cursor (char row, char column);

#endif