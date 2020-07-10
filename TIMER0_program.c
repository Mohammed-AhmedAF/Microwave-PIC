#include "Std_Types.h"
#include "Macros.h"
#include "COMMON_private.h"
#include "TIMER0_private.h"
#include "TIMER0_interface.h"

void (*ptrFunc) (void);

void TIMER0_vidInit(u8 u8TimerMode, u8 u8Prescaler)
{
    if (u8TimerMode == TIMER0_MODE_COUNTER)
    {
        SET_BIT(OPTION_REG,5);
    }
    else
    {
        CLEAR_BIT(OPTION_REG,5);
    }
    
    /*Setting prescaler*/
    switch(u8Prescaler)
    {
        case TIMER0_PS_2:
            CLEAR_BIT(OPTION_REG,0);
            CLEAR_BIT(OPTION_REG,1);
            CLEAR_BIT(OPTION_REG,2);
            break;
        case TIMER0_PS_4:
            SET_BIT(OPTION_REG,0);
            CLEAR_BIT(OPTION_REG,1);
            CLEAR_BIT(OPTION_REG,2);
            break;
        case TIMER0_PS_8:
            CLEAR_BIT(OPTION_REG,0);
            SET_BIT(OPTION_REG,1);
            CLEAR_BIT(OPTION_REG,2);
            break;
        case TIMER0_PS_16:
            SET_BIT(OPTION_REG,0);
            SET_BIT(OPTION_REG,1);
            CLEAR_BIT(OPTION_REG,2);
            break;
        case TIMER0_PS_32:
            CLEAR_BIT(OPTION_REG,0);
            CLEAR_BIT(OPTION_REG,1);
            SET_BIT(OPTION_REG,2);
            break;
        case TIMER0_PS_64:
            SET_BIT(OPTION_REG,0);
            CLEAR_BIT(OPTION_REG,1);
            SET_BIT(OPTION_REG,2);
            break;
        case TIMER0_PS_128:
            CLEAR_BIT(OPTION_REG,0);
            SET_BIT(OPTION_REG,1);
            SET_BIT(OPTION_REG,2);
            break;
        case TIMER0_PS_256:
            SET_BIT(OPTION_REG,0);
            SET_BIT(OPTION_REG,1);
            SET_BIT(OPTION_REG,2);
            break;
    }    
}

void TIMER0_vidPutISR(void (*pF) (void))
{
    ptrFunc = pF;
}

