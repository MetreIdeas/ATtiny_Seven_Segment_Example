/* Seven_Segment_Display.h */

/* Seven segment display driver for Atmel ATtiny */

/* Will Sakran */
/* Metre Ideas and Design */
/* Copyright (c) 2015  */

/* www.metreideas.com */


#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

#define TRUE  1
#define FALSE 0

#define DIGIT1			PORTB4	// common connection for digit 1
#define DIGIT2			PORTB5	// common connection for digit 2

/* SEGMENT ON OFF states */
/* This assumes an active high state */
#define	DIGIT1_ON		PORTB |= (1 << DIGIT1);
#define DIGIT1_OFF		PORTB &= ~(1 << DIGIT1);
#define	DIGIT2_ON		PORTB |= (1 << DIGIT2);
#define DIGIT2_OFF		PORTB &= ~(1 << DIGIT2);

/* Define either COMMON_ANODE or COMMON_CATHODE  */
#define COMMON_ANODE

/* Function Prototypes */
void init_seven_segment_display(void);
void clear_seven_segment_display(void);
void display_value(uint8_t value);
void display_digit(uint8_t value, uint8_t digit, uint8_t decimal);
void display_test(void);

#endif