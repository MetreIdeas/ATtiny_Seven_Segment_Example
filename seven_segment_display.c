/* Seven_Segment_Display.c */

/* Seven segment display driver for Atmel ATtiny */

/* Will Sakran				*/
/* Metre Ideas and Design	*/
/* Copyright (c) 2015		*/

/* www.metreideas.com */


#include <avr/io.h>
#include "seven_segment_display.h"
#include <util/delay.h>


/* Define the segments that make up the various numbers */
/*	
        A
       --- 
  F   /  /   B
      ---      G
 E   /  /   C 
     --- .  P
    D

*/
									   /* PGFEDCBA */
static unsigned char digitCode[11] = {	0b11000000, //0
										0b11111001, //1
										0b10100100, //2
										0b10110000, //3
										0b10011001, //4
										0b10010010, //5
										0b10000010, //6
										0b11111000, //7
										0b10000000, //8
										0b10010000, //9
										0b11111111 }; //segment off


/*
 * Initialize the output pins used by the micro to talk to the
 * shift register that drives the seven segment display module.
*/   
void init_seven_segment_display(void)
{
	DDRA |= (1 << SERIAL_DATA_PIN) | (1 << SERIAL_CLK_PIN);	// set serial data and clock pins as outputs
	DDRA |= (1 << REG_CLOCK_PIN);							// set register clock pin as output
	DDRB |= (1 << DIGIT1) | (1 << DIGIT2);					// set digit control pins as outputs

	DISPLAY_PORT &= ~((1 << SERIAL_DATA_PIN) | (1 << SERIAL_CLK_PIN));		// clear the serial data and clock pins
	DISPLAY_PORT &= ~(1 << REG_CLOCK_PIN);									// clear the register clock pin
	PORTB &= ~((1 << DIGIT1) | (1 << DIGIT2));								// set digit control pins as outputs
	
}


/*
 * Turn of all the digits on the seven segment display module.
*/ 
void clear_seven_segment_display(void)
{
	DIGIT1_OFF
	DIGIT2_OFF
}


/*
 * Break the value to be displayed into component digits. For a two-digit
 * display this is the tens place and the ones place. Individual digits are
 * then sent to the display_digit function.
 *
 * value - the full number to be displayed
*/ 
void display_value(uint8_t value)
{
	uint8_t tens, ones;
	
	tens = value / 10;
	ones = value % 10;

	display_digit(tens, 1, FALSE);		// tens place is the first digit, no decimal point
	display_digit(ones, 2, FALSE);		// ones place is the second digit, no decimal point
}


/*
 * Map the value to the proper digit code and shift the bits out serially.
 * Bits are clocked into the shift register one at a time. After all eight
 * bits are shifted in, the register clock latches the bits to the output of
 * the shift register.
 *
 * value - the single-digit number to be displayed (0 - 9)
 * digit - which digit location to display the number
 * decimal - TRUE = show decimal point for that digit
*/ 
void display_digit(uint8_t value, uint8_t digit, uint8_t decimal)
{
	uint8_t serial_data;
	uint8_t i;

	serial_data = digitCode[value];
	if(decimal == TRUE)
		serial_data &= 0x7F;		// clear the decimal point bit to enable decimal

#ifdef COMMON_CATHODE
	~serial_data;
#endif

	for (i = 0; i < 8; i++)
	{
		if(serial_data & 0x80)				// if true, write a 1 to the pin
			DISPLAY_PORT |= (1 << SERIAL_DATA_PIN);
		else								// else, write a 0 to the pin
			DISPLAY_PORT &= ~(1 << SERIAL_DATA_PIN);
		
		_delay_us(50);
		
		toggle_serial_clock();
		
		serial_data = serial_data << 1;		// shift the next data bit over
	}
	
	toggle_register_clock();				// latch the data into the output register

	if(digit == 1) {
		DIGIT1_ON
		DIGIT2_OFF
	}

	if(digit == 2) {
		DIGIT2_ON
		DIGIT1_OFF
	}
}


/*
 * Set the serial clock pin high, delay, then set the serial clock pin low.
*/ 
void toggle_serial_clock(void)
{
	DISPLAY_PORT |= (1 << SERIAL_CLK_PIN);
	_delay_us(50);
	DISPLAY_PORT &= ~(1 << SERIAL_CLK_PIN);
}


/*
 * Set the register clock pin high, delay, then set the serial clock pin low.
*/
void toggle_register_clock(void)
{
	DISPLAY_PORT |= (1 << REG_CLOCK_PIN);
	_delay_us(50);
	DISPLAY_PORT &= ~(1 << REG_CLOCK_PIN);
}


/*
 * Test each of the digits by counting from 0 to 9.
*/
void display_test(void)
{
	uint8_t counter;
	
	/* test the first digit and the decimal point */
	for (counter=0 ; counter<10 ; counter++)
	{
		display_digit(counter, 1, TRUE);
		_delay_ms(200);
	}
	
	/* test the second digit and the decimal point */
	for (counter=0 ; counter<10 ; counter++)
	{
		display_digit(counter, 2, TRUE);
		_delay_ms(200);
	}
}