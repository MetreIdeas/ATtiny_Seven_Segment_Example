/* Color_Maker.h */

/* Will Sakran */
/* Metre Ideas and Design */
/* Copyright (c) 2015 */

/* www.metreideas.com */


#ifndef SEVEN_SEGMENT_EXAMPLE_H
#define SEVEN_SEGMENT_EXAMPLE_H

/* LED ON OFF states */
#define	LED_ON		PORTB |= (1 << PORTB3);
#define LED_OFF		PORTB &= ~(1 << PORTB3);

//! Set bits corresponding to pin usage above
#define PORTA_MASK  (1 << PORTA1)|(1 << PORTA2)|(1 << PORTA4)

void board_init(void);
void configure_sleep(void);

#endif