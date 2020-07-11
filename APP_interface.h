/* 
 * File:   APP_interface.h
 * Author: Mohammed
 *
 * Created on February 28, 2020, 2:38 AM
 */

#ifndef APP_INTERFACE_H
#define	APP_INTERFACE_H

void APP_vidRestartSystem(void);
void APP_vidConvertToTime(u8);
void APP_vidCountOVF(void);
void APP_vidInit(void);
void APP_vidTestText(void);
void APP_vidStartHeating(void);
void APP_vidChangeKeyboardState(void);
void APP_vidCheckWhileHeating(void);
u8 APP_u8CheckToStart(void);
void APP_vidControlHeating(u8);
u8 APP_u8CheckFood(void);
u8 APP_u8CheckDoor(void);
u8 APP_u8CheckStart(void);

/*Macros for conditions*/
#define APP_FOOD_IN 0
#define APP_FOOD_OUT 1

#define APP_DOOR_CLOSED 1
#define APP_DOOR_OPEN 0

#define APP_HEAT_ON 1
#define APP_HEAT_OFF 0

/*Macros for pins*/
#define APP_LAMP_PORT DIO_PORTC
#define APP_LAMP_PIN DIO_PIN7

#define APP_DOOR_PORT DIO_PORTB
#define APP_DOOR_PIN DIO_PIN4

#define APP_WEIGHT_PORT DIO_PORTB
#define APP_WEIGHT_PIN DIO_PIN5

#define APP_START_PORT DIO_PORTB 
#define APP_START_PIN DIO_PIN3

#define APP_MOTOR_PORT DIO_PORTC
#define APP_MOTOR_PIN DIO_PIN2

#define APP_CANCEL_PORT DIO_PORTA
#define APP_CANCEL_PIN DIO_PIN5

/**/
#define APP_CANCEL_PRESSED 0
#define APP_CANCEL_UNPRESSED 1

#define APP_START_PRESSED 0
#define APP_START_UNPRESSED 1


#endif	/* APP_INTERFACE_H */

