/* 
 * File:   COMMON_private.h
 * Author: Mohammed
 *
 * Created on February 23, 2020, 5:48 PM
 */

#ifndef COMMON_PRIVATE_H
#define	COMMON_PRIVATE_H

#define OPTION_REG * ((volatile u8 *) 0x81)
#define _XTAL_FREQ 4000000

#define SSPSTAT * ((u8*) 0x94)
#define SSPCON1 * ((u8*) 0x14)
#define SSPBUFF * ((u8*) 0x13)
#define ADCON1 * ((volatile u8*) 0x9F)



#endif	/* COMMON_PRIVATE_H */

