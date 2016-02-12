/*
 * seven_segment_example.c
 *
 * Created: 02/11/2016
 * Author: Will Sakran
 * Metre Ideas and Design
 * Copyright (c) 2016
 *
 * This program is a driver example for a two-digit seven segment LED display module.
 * The two digits of the display module share a common set of data lines.
 * Therefore, to display a two-digit number the individual digits must be displayed
 * one at time and cycled back and forth continuously.

 * This code was originally developed for use with the Lite-On LTD2601 display
 * module (common anode).
 *
 * Developed for use with Atmel ATtiny261A / ATtiny461A / ATtiny861A
 * For ATtiny261A/461A/861A Prototyping boards go to
 * www.metreideas.com
 *
 */ 

#include <stdint.h>
#include "seven_segment_example.h"
#include "seven_segment_display.h"
#include <avr/io.h>

volatile uint8_t keep_on_loopin=1;
volatile uint8_t timer_flag=0;

/**
 * \brief Main routine
 */
int main(void)
{
	uint8_t i;
	uint8_t counter;
	 
	board_init();
	
	init_seven_segment_display();
	clear_seven_segment_display();
	display_test();
	
	while (keep_on_loopin) {
		
		for(counter=0 ; counter < 100 ; counter++)
		{
			// The value sent to the display gets looped several times.
			// To increase the length of time that a digit is displayed,
			// increase the number of loops.
			for(i=0 ; i < 20 ; i++)
				display_value(counter);
		}
		
		clear_seven_segment_display();
		
	} // end while
} // end main


void board_init(void)
{
	/* Pins default to input after reset */
	
	DDRB |= (1 << DIGIT1) | (1 << DIGIT2);	// set common digit controls as outputs 
	DDRA = 0xFF;							// set all port A pins as outputs (digit segment data)
}