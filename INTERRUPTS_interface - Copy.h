/* 
 * File:   INTERRUPTS_interface.h
 * Author: Mohammed
 *
 * Created on February 20, 2020, 12:52 PM
 */

#ifndef INTERRUPTS_INTERFACE_H
#define	INTERRUPTS_INTERFACE_H

void INTERRUPTS_vidEnableGlobalInterrupt(void);
void INTERRUPTS_vidDisableGlobalInterrupt(void);
void INTERRUPTS_vidEnablePeripheralInterrupt(void);
void INTERRUPTS_vidDisablePeripheralInterrupt(void);
void INTERRUPTS_vidEnableInterrupt(u8);
void INTERRUPTS_vidDisableInterrupt(u8);
void INTERRUPTS_vidSetExtInterruptEdge(u8);
void INTERRUPTS_vidPutISR(u8,void (*pt) (void));

#define INTERRUPTS_TIMER0_OVF 0
#define INTERRUPTS_EXT 1
#define INTERRUPTS_EDGE_RISING 0
#define INTERRUPTS_EDGE_FALLING 1


#endif	/* INTERRUPTS_INTERFACE_H */

