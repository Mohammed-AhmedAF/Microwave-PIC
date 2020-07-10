/* 
 * File:   I2C_interface.h
 * Author: Mohammed
 *
 * Created on February 24, 2020, 10:16 AM
 */

#ifndef I2C_INTERFACE_H
#define	I2C_INTERFACE_H

void I2C_vidInit(u8);
void I2C_vidSendStart(void);
void I2C_vidSendRepeatedStart(void);
void I2C_vidSendByte(u8);
void I2C_vidSendStop(void);
u8 I2C_u8CheckACK(u8);
u8 I2C_u8ReceiveByte(void);


#define I2C_MODE_MASTER 0

#endif	/* I2C_INTERFACE_H */

