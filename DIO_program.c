#include "Macros.h"
#include "Std_Types.h"
#include "COMMON_private.h"
#include "DIO_private.h"
#include "DIO_interface.h"

 void DIO_vidSetPinDirection(u8 u8PortNumber, u8 u8PinNumber, u8 u8Direction)
{
    switch(u8PortNumber)
    {
        case DIO_PORTA:
            if (u8Direction == DIO_OUTPUT)
            {
                CLEAR_BIT(TRISA,u8PinNumber);
            }
            else {
                SET_BIT(TRISA,u8PinNumber);
            }
            break;
        case DIO_PORTB:
            if (u8Direction == DIO_OUTPUT)
            {
                CLEAR_BIT(TRISB,u8PinNumber);
            }
            else {
                SET_BIT(TRISB,u8PinNumber);
            }
            break;
        case DIO_PORTC:
            if (u8Direction == DIO_OUTPUT)
            {
                CLEAR_BIT(TRISC,u8PinNumber);
            }
            else {
                SET_BIT(TRISC,u8PinNumber);
            }
            break;
        case DIO_PORTD:
            if (u8Direction == DIO_OUTPUT)
            {
                CLEAR_BIT(TRISD,u8PinNumber);
            }
            else {
                SET_BIT(TRISD,u8PinNumber);
            }
            break;
        case DIO_PORTE:
            if (u8Direction == DIO_OUTPUT)
            {
                CLEAR_BIT(TRISE,u8PinNumber);
            }
            else {
                SET_BIT(TRISE,u8PinNumber);
            }
            if (u8PinNumber <= DIO_PIN2)
            {
                SET_BIT(ADCON1,u8PinNumber);
            }
            break;
    }
}

void DIO_vidSetPinValue(u8 u8PortNumber, u8 u8PinNumber, u8 u8Value) 
{
    switch(u8PortNumber) {
		case DIO_PORTA:
			if (u8Value == STD_HIGH) {
				SET_BIT(PORTA,u8PinNumber);
			}
			else {
				CLEAR_BIT(PORTA,u8PinNumber);
			}
			break;
		case DIO_PORTB:
			if (u8Value == STD_HIGH) {
				SET_BIT(PORTB,u8PinNumber);
			}
			else {
				CLEAR_BIT(PORTB,u8PinNumber);
			}	
			break;
		case DIO_PORTC:
			if (u8Value == STD_HIGH) {
				SET_BIT(PORTC,u8PinNumber);
			}
			else {
				CLEAR_BIT(PORTC,u8PinNumber);
			}						
			break;
		case DIO_PORTD:
			if (u8Value == STD_HIGH) {
				SET_BIT(PORTD,u8PinNumber);
			}
			else {
				CLEAR_BIT(PORTD,u8PinNumber);
			}							
			break;
		case DIO_PORTE:
			if (u8Value == STD_HIGH)
			{
                SET_BIT(PORTE,u8PinNumber);
			}
			else {
				CLEAR_BIT(PORTE,u8PinNumber);
			}
            break;
	}
}

void DIO_vidTogglePin(u8 u8PortNumber, u8 u8PinNumber)
{
    switch (u8PortNumber)
    {
        case DIO_PORTA:
            TOGGLE_BIT(PORTA,u8PinNumber);
            break;
        case DIO_PORTB:
            TOGGLE_BIT(PORTB,u8PinNumber);
            break;
        case DIO_PORTC:
            TOGGLE_BIT(PORTC,u8PinNumber);
            break;
        case DIO_PORTD:
            TOGGLE_BIT(PORTD,u8PinNumber);
            break;
        case DIO_PORTE:
            TOGGLE_BIT(PORTE,u8PinNumber);
            break;
    }
}

u8 DIO_u8GetPinValue(u8 u8PortNumber, u8 u8PinNumber)
{
    switch (u8PortNumber)
    {
        case DIO_PORTA:
            return GET_BIT(PORTA,u8PinNumber);
            break;
        case DIO_PORTB:
            return GET_BIT(PORTB,u8PinNumber);
            break;
        case DIO_PORTC:
            return GET_BIT(PORTC,u8PinNumber);
            break;
        case DIO_PORTD:
            return GET_BIT(PORTD,u8PinNumber);
            break;
        case DIO_PORTE:
            return GET_BIT(PORTE,u8PinNumber);
            break;
    }
}

void DIO_vidSetPortValue(u8 u8PortNumber, u8 u8PortValue)
{
    switch(u8PortNumber)
    {
        case DIO_PORTA:
            PORTA = u8PortValue;
            break;
        case DIO_PORTB:
            PORTB = u8PortValue;
            break;
        case DIO_PORTC:
            PORTC = u8PortValue;
            break;
        case DIO_PORTD:
            PORTD = u8PortValue;
            break;
    }
}

void DIO_vidSetPortDirection(u8 u8PortNumber, u8 u8PortDirection)
{
    switch(u8PortNumber)
    {
        case DIO_PORTA:
            TRISA = u8PortDirection;
            break;
        case DIO_PORTB:
            TRISB = u8PortDirection;
            break;
        case DIO_PORTC:
            TRISC = u8PortDirection;
            break;
        case DIO_PORTD:
            TRISD = u8PortDirection;
            break;
        case DIO_PORTE:
            TRISE = u8PortDirection;
    }
}

void DIO_vidControlPullUp(u8 u8PullState)
{
    if (u8PullState == DIO_PULLUP)
    {
        CLEAR_BIT(OPTION_REG,7);
    }
    else
    {
        SET_BIT(OPTION_REG,7);
    }
}