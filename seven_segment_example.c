/*
 * seven_segment_example.c
 *
 * Created: 02/11/2016
 * Author: Will Sakran
 * Metre Ideas and Design
 * Copyright (c) 2016
 *
 * This program reads an analog input on ADC0 (pin PA0). An external interrupt
 * (INT0 on pin PB2) is also provided which can be used to trigger the chip to
 * store the current analog input value to a reference variable. Current samples
 * can then be compared to this reference value.
 *
 * Developed for use with Atmel ATtiny261A / ATtiny461A / ATtiny861A
 * For ATtiny261A/461A/861A Prototyping boards go to
 * www.metreideas.com
 *
 */ 

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "seven_segment_example.h"
#include "seven_segment_display.h"
#include <avr/power.h>
#include <avr/io.h>
#include <util/delay.h>

/* set the correct clock frequency based on fuse settings or external clock/crystal
 * has to be done before including delay.h */
//#define F_CPU 8000000UL

volatile uint8_t keep_on_loopin=1;
volatile uint8_t timer_flag=0;

/**
 * \brief Main routine
 */
int main(void)
 {
	board_init();
	
	init_seven_segment_display();
	clear_seven_segment_display();
	
	TIFR = (1 << TOV0);			// clear interrupt flag
	TIMSK = (1 << TOIE0);		// enable overflow interrupt
	TCCR0B = (1 << CS00);		// start timer, no prescaler
	
	sei();						// Enable interrupts
	
	while (keep_on_loopin) {
		
		display_test();
		
		clear_seven_segment_display();
		_delay_ms(200);
		_delay_ms(200);
		_delay_ms(200);
		_delay_ms(200);
		_delay_ms(200);
			
	} // end while
	
} // end main


void board_init(void)
{
	/* Pins default to input after reset */
	
	DDRB = 0x38;	// Set PortB pins 3, 4, and 5 as outputs
//	PORTA = 0xAE;	// enable pull-ups on unused pins
	PORTA |= (1 << PORTA0);		// enable pull-up on the button input
	DDRA = PORTA_MASK;			// set necessary port pins to output for LEDs

	  
	LED_OFF
}