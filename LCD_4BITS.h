/*
 * LCD_4BITS.h
 *
 * Created: 3/11/2019 1:20:43 PM
 *  Author: MohamedNgdy
 */ 


#ifndef LCD_4BITS_H_
#define LCD_4BITS_H_

#include <avr/io.h>
#include <util/delay.h>

#define LCD_PORT	PORTB
#define LCD_DDR		DDRB
#define LCD_PIN		PINB
#define LCD_RW		PINB1
#define LCD_RS		PINB0
#define LCD_E		PINB2



void lcd_command(unsigned char command)
{
	LCD_PORT = (LCD_PORT & 0X0F) | (command & 0xF0);
	LCD_PORT &= ~(1 << LCD_RS);
	LCD_PORT &= ~(1 << LCD_RW);
	LCD_PORT |= 1 << LCD_E;
	_delay_ms(10);
	LCD_PORT &= ~(1 << LCD_E);
	
	_delay_ms(1);
	
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4) ;
	LCD_PORT |= 1 << LCD_E;
	_delay_ms(10);
	LCD_PORT &= ~(1 << LCD_E);
}

void lcd_data(unsigned char data)
{
	LCD_PORT = (LCD_PORT & 0X0F) | (data & 0xF0);
	LCD_PORT |= 1 << LCD_RS;
	LCD_PORT &= ~(1 << LCD_RW);
	LCD_PORT |= 1 << LCD_E;
	_delay_ms(10);
	LCD_PORT &= ~(1 << LCD_E);
	
	_delay_ms(1);
	
	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4) ;
	LCD_PORT |= 1 << LCD_E;
	_delay_ms(10);
	LCD_PORT &= ~(1 << LCD_E);
}

void lcd_init()
{
	LCD_DDR = 0xFF;
	
	LCD_PORT &= ~(1 << LCD_E);
	_delay_ms(2);
	lcd_command(0x33);					// for 4 bit mode
	lcd_command(0x32);					// for 4 bit mode
	lcd_command(0x28);					// 2 lines , 5*7 matrix in 4bit mode
	lcd_command(0x0E);					// display on , cursor on
	lcd_command(0x01);					// clear screen
	lcd_command(0x06);					// shift cursor right
}

void goto_xy(unsigned char x, unsigned char y)
{
	unsigned char rows[] = {0x80, 0xc0, 0x94, 0xD4};					// the addresses of first of every column
	lcd_command(rows[y-1] + (x-1));										// send the address of first column plus the possition we need
}

void lcd_write(unsigned char *string)
{
	unsigned char i = 0;
	while(string[i] != 0)
	{
		lcd_data(string[i]);
		i++;
	}
}



#endif /* LCD_4BITS_H_ */