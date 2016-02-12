/* Seven_Segment_Display.c */

/* Seven segment display driver for Atmel ATtiny */

/* Will Sakran				*/
/* Metre Ideas and Design	*/
/* Copyright (c) 2015		*/

/* www.metreideas.com */


#include <avr/io.h>
#include "seven_segment_display.h"

/* set the correct clock frequency based on fuse settings or external clock/crystal
 * has to be done before including delay.h */
#define F_CPU 1000000UL

#include <util/delay.h>


/* Define the segments that make up the various numbers */
/*	
        A
       --- 
    F /  /  B
      ---  G
   E /  /  C 
     --- . P
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
 * Initialize the output pins used by the micro
 * that drive the seven segment display module.
*/   
void init_seven_segment_display(void)
{
	DDRB |= (1 << DIGIT1) | (1 << DIGIT2);					// set digit control pins as outputs
	PORTB &= ~((1 << DIGIT1) | (1 << DIGIT2));				// set digit control pins to zero
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
 * Map the desired value to the proper digit code.
 *
 * value - the single-digit number to be displayed (0 - 9)
 * digit - which digit location to display the number
 * decimal - TRUE = show decimal point for that digit
*/ 
void display_digit(uint8_t value, uint8_t digit, uint8_t decimal)
{
	uint8_t segment_data;

	segment_data = digitCode[value];
	if(decimal == TRUE)
		segment_data &= 0x7F;		// clear the decimal point bit to enable decimal

#ifdef COMMON_CATHODE
	segment_data = ~segment_data;
#endif

	PORTA = segment_data;

	if(digit == 1) {
		DIGIT1_ON
		DIGIT2_OFF
	}

	if(digit == 2) {
		DIGIT2_ON
		DIGIT1_OFF
	}
	
	// Delay so that the current digit is on for a small amount of time
	// before the next digit is displayed.
	_delay_ms(5);
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