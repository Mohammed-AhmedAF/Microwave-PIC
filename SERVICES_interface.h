/* 
 * File:   SERVICES_interface.h
 * Author: Mohammed
 *
 * Created on February 20, 2020, 9:49 PM
 */

#ifndef SERVICES_INTERFACE_H
#define	SERVICES_INTERFACE_H

void SERVICES_delay_ms(u16);
u8 SERVICES_u8WriteCharacter(void);
/*DeleteCharacter will return the x-position of the
 character deleted*/
u8 SERVICES_vidDeleteCharacter(u8);
void SERVICES_vidExecWhenPressed(u8,void(*pt)(void));

#define SERVICES_KEY_ENTER 0
#define SERVICES_KEY_BACK 1
#define SERVICES_KEY_DEL 2


#endif	/* SERVICES_INTERFACE_H */