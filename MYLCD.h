/*
 * MYLCD.h
 *
 * Created: 3/10/2019 5:03:51 PM
 *  Author: MohamedNgdy
 */ 


#ifndef MYLCD_H_
#define MYLCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

// connect ENABLE of LCD to PD1 of PORTD
// connect RS of LCD to PD0 of PORTD 
// connect D0-D7 to all PORTC


// initialize the settings of LCD
void initializeLcd()
{
	unsigned int sd[10] ={0x38, 0x0E, 0x01, 0x80, 0};	// list of initial commands
	for (unsigned char k=0; sd[k]!=0; k++)
	{
		PORTD = 0x02;									// set PORTD to 0b00000010 to Enable the LCD and set RS	to zero to enable send commands
		PORTC = sd[k];									// send next command to LCD 
		_delay_ms(1);
		PORTD = 0x00;									// disable the LCD
		_delay_ms(100);
	}
}

// use this to send any message to LCD at the default place of cursor
void writestring(unsigned char * charachter)
{
	// go throw the array of characters and send them
	for(unsigned char j=0; charachter[j]!=0; j++)
	{
		PORTD = 0x03;									// send 0b00000011 to LCD to enable it and enable also send data
		PORTC = charachter[j];							// send character to the LCD throw PORTC
		_delay_ms(1);
		PORTD = 0x01;									// disable LCD
	}
	_delay_ms(1);
}


// use this to write one char to LCD in defalut cursor place
void writeChar(unsigned char ch)
{
	PORTD = 0x03;										// enable LCD and make it recive data
	PORTC = ch;											// send the char to LCD throw PORTC
	_delay_ms(1);	
	PORTD = 0x01;										// disable LCD
	_delay_ms(1);
}


// use this method to change the cursor place 
void changeCursor(unsigned char x, unsigned char y)
{
	unsigned char rows[2] = {0, 64};					// this define that the LCD is just two rows
	PORTD = 0x02;										// make LCD recive commands by put RS to zero and enable LCD
	PORTC = (0x80 + (rows[x-1] + (y-1)));				// send our command to LCD throw PORTC
	_delay_ms(1);
	PORTD = 0x00;										// disable LCD
}


// use this to write a char on LCD by detect it's position on LCD
void writeCharAtSpecificPosition(unsigned char x, unsigned char y, char ch)
{
	changeCursor(x, y);									// use the function of change cursor
	writeChar(ch);										// use the function of writerChar
	_delay_ms(1);
}


// use this to write string on specific position you need on LCD
void writeStringAtSpecificPosition(unsigned char x, unsigned char y, char *string)
{
	changeCursor(x, y);									// use function change cursor
	writestring(string);								// use function writestring
	_delay_ms(1);
}


// use this if u need to write an integer
void writeNumbers(int number)
{
	char strNum[10];
	itoa(number, strNum, 10);							// convert the integer to an array of chars
	for(unsigned char i = 0; i<strlen(strNum); i++)
	{
		writeChar(strNum[i]);							// writer each char to screen 
	}
}




#endif /* MYLCD_H_ */