/* 
 * File:   DIO_interface.h
 * Author: Mohammed
 *
 * Created on February 19, 2020, 9:15 AM
 */

#ifndef DIO_INTERFACE_H
#define	DIO_INTERFACE_H

void DIO_vidSetPinDirection(u8,u8,u8);
void DIO_vidSetPinValue(u8,u8,u8);
u8 DIO_u8GetPinValue(u8,u8);
void DIO_vidTogglePin(u8,u8);
void DIO_vidSetPortValue(u8,u8);
void DIO_vidSetPortDirection(u8,u8);
void DIO_vidControlPullUp(u8);

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3
#define DIO_PORTE 4

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_OUTPUT 0
#define DIO_INPUT 1

#define DIO_OUT 0
#define DIO_IN 1

#define DIO_PULLUP 1
#define DIO_PULLUP_NO 0

#endif	/* DIO_INTERFACE_H */

