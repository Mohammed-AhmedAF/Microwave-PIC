/* 
 * File:   KEYPAD_interface.h
 * Author: Mohammed
 *
 * Created on February 20, 2020, 11:13 PM
 */

#ifndef KEYPAD_INTERFACE_H
#define	KEYPAD_INTERFACE_H

#define HOLD_BUTTON 0

#define ROW0_PORT DIO_PORTD
#define ROW0_PIN 0
#define ROW1_PORT DIO_PORTD
#define ROW1_PIN 1
#define ROW2_PORT DIO_PORTD
#define ROW2_PIN 2
#define ROW3_PORT DIO_PORTD
#define ROW3_PIN 3

#define COL0_PORT DIO_PORTB
#define COL0_PIN 0
#define COL1_PORT DIO_PORTB
#define COL1_PIN 1
#define COL2_PORT DIO_PORTB
#define COL2_PIN 2

#define KEYPAD_DELETE '*'
#define KEYPAD_ENTER '#'
#define KEYPAD_DIVIDE '/'

void KEYPAD_vidInit(void);
u8 KEYPAD_u8GetKey(void);

#endif	/* KEYPAD_INTERFACE_H */

