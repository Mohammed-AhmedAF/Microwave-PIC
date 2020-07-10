#include "Std_Types.h"
#include "Macros.h"
#include "INTERRUPTS_private.h"
#include "INTERRUPTS_interface.h"
#include "COMMON_private.h"
#include <pic16f877.h>


void (*ptrFunc_Arr[10])(void);

void INTERRUPTS_vidEnableGlobalInterrupt(void)
{
    SET_BIT(INTCON,7);
}

void INTERRUPTS_vidDisableGlobalInterrupt(void)
{
    CLEAR_BIT(INTCON,7);
}

void INTERRUPTS_vidEnablePeripheralInterrupt(void)
{
    SET_BIT(INTCON,6);
}

void INTERRUPTS_vidDisablePeripheralInterrupt(void)
{
    CLEAR_BIT(INTCON,6);
}

void INTERRUPTS_vidEnableInterrupt(u8 u8InterruptID)
{
    switch(u8InterruptID)
    {
        case INTERRUPTS_TIMER0_OVF:
            SET_BIT(INTCON,5);
            break;
        case INTERRUPTS_EXT:
            SET_BIT(INTCON,4);
            break;
    }
}

void INTERRUPTS_vidSetExtInterruptEdge(u8 u8Edge)
{
    if (u8Edge == INTERRUPTS_EDGE_RISING)
    {
        SET_BIT(OPTION_REG,6);
    }
    else {
        CLEAR_BIT(OPTION_REG,6);     
    }
}

void INTERRUPTS_vidDisableInterrupt(u8 u8InterruptID)
{
    switch(u8InterruptID)
    {
        case INTERRUPTS_TIMER0_OVF:
            CLEAR_BIT(INTCON,5);
            break;
        case INTERRUPTS_EXT:
            CLEAR_BIT(INTCON,5);
            break;
    }
}

void INTERRUPTS_vidPutISR(u8 u8InterruptID, void (*ptFun) (void))
{
    ptrFunc_Arr[u8InterruptID] = ptFun;
}


void interrupt ISR()
{
    if (GET_BIT(INTCON,2) == 1)
    {

        ptrFunc_Arr[INTERRUPTS_TIMER0_OVF]();        
        /*Clearing TMR0IF*/
        CLEAR_BIT(INTCON,2);
    }
    if (GET_BIT(INTCON,1) == 1)
    {
        ptrFunc_Arr[INTERRUPTS_EXT]();
        CLEAR_BIT(INTCON,1);
    }
}