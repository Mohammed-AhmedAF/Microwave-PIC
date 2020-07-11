#include <xc.h>
#include "config.h"
#include "Macros.h"
#include "Std_Types.h"
#include "INTERRUPTS_interface.h"
#include "LCD_interface.h"
#include "DIO_interface.h"
#include "ADC_private.h"
#include "KEYPAD_interface.h"
#include "APP_interface.h"
#include "SERVICES_interface.h"
#include "TIMER0_interface.h"
#include "COMMON_private.h"

#define _XTAL_FREQ 4000000


extern u8 u8KeyboardState;
extern u8 u8HeatState;
extern u8 u8TimeEntered;
u8 u8FoodState, u8DoorState;

u8 u8Condition;
void main(void)
{

    APP_vidInit();
    
    while (1)
    {
        while (u8KeyboardState == 1)
        {
            SERVICES_u8WriteCharacter();
        }
        while (u8HeatState == APP_HEAT_OFF && u8TimeEntered == 1)
        {
            APP_u8CheckFood();
            APP_u8CheckDoor();
            u8Condition = 0;
            u8Condition |= APP_u8CheckFood();
            if (u8Condition == 1)
            {
                u8Condition |= APP_u8CheckDoor()<<1;
                if (u8Condition == 3)
                {
                    u8Condition |= APP_u8CheckStart()<<2;
                }
            }
            if (u8Condition == 0x07)
            {   
                APP_vidStartHeating();
            }  
        }
        APP_vidCheckWhileHeating();
        
    }
}