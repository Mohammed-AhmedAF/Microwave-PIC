/* 
 * File:   TIMER0_interface.h
 * Author: Mohammed
 *
 * Created on February 20, 2020, 11:36 AM
 */

#ifndef TIMER0_INTERFACE_H
#define	TIMER0_INTERFACE_H

void TIMER0_vidInit(u8,u8);
void TIMER0_vidPutISR(void (*pt)(void));

#define TIMER0_MODE_TIMER 0
#define TIMER0_MODE_COUNTER 1

#define TIMER0_PS_2 0
#define TIMER0_PS_4 1
#define TIMER0_PS_8 2
#define TIMER0_PS_16 3
#define TIMER0_PS_32 4
#define TIMER0_PS_64 5
#define TIMER0_PS_128 6
#define TIMER0_PS_256 7


#endif	/* TIMER0_INTERFACE_H */

