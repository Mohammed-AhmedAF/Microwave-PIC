#include <xc.h>
#include "Macros.h"
#include "Std_Types.h"
#include "INTERRUPTS_interface.h"
#include "DIO_interface.h"
#include "KEYPAD_interface.h"
#include "LCD_interface.h"
#include "SERVICES_interface.h"
#include "TIMER0_interface.h"
#include "SCHEDULER_interface.h"
#include "APP_interface.h"

#define _XTAL_FREQ 4000000

extern u8 i;
extern u8 u8CurrXPos, u8CurrYPos;
extern u8 u8UserTextIndex;
extern u8 u8UserInput[10];
extern u8 u8UserTextEnd;
u8 u8RestartSys;
volatile u16 u16Seconds;
volatile u8 u8HeatState = APP_HEAT_OFF;

u8 u8TimeEntered = 0;

u8 u8KeyboardState = 1;
/*Timer variable*/
volatile u16 u16OVFCount = 0;

u8 u8FoodState, u8DoorState;

void APP_vidInit(void) {
    SERVICES_vidExecWhenPressed(SERVICES_KEY_ENTER, APP_vidChangeKeyboardState);
    SERVICES_vidExecWhenPressed(SERVICES_KEY_DEL, APP_vidRestartSystem);

    /*Configuring pin of door*/
    DIO_vidSetPinDirection(APP_DOOR_PORT, APP_DOOR_PIN, DIO_INPUT);

    /*Start pin configuration*/
    DIO_vidSetPinDirection(APP_START_PORT, APP_START_PIN, DIO_INPUT);

    DIO_vidSetPinDirection(APP_CANCEL_PORT, APP_CANCEL_PIN, DIO_INPUT);
    DIO_vidSetPinValue(APP_CANCEL_PORT, APP_CANCEL_PIN, STD_HIGH);

     /*Motor configuration*/
    DIO_vidSetPinDirection(APP_MOTOR_PORT, APP_MOTOR_PIN, DIO_OUTPUT);

    /*Configuring pins of weight pins*/
    DIO_vidSetPinDirection(APP_WEIGHT_PORT, APP_WEIGHT_PIN, DIO_INPUT);

    DIO_vidControlPullUp(DIO_PULLUP);
    INTERRUPTS_vidEnablePeripheralInterrupt();
    INTERRUPTS_vidEnableGlobalInterrupt();
    

    /*Timer0 configuration*/
    TIMER0_vidInit(TIMER0_MODE_TIMER, TIMER0_PS_2);
    INTERRUPTS_vidPutISR(INTERRUPTS_TIMER0_OVF,APP_vidCountOVF);

    LCD_vidInit();
    KEYPAD_vidInit();
    
    APP_vidRestartSystem();

   
}

static void APP_vidRestartSystem(void) { /*Cancel pin configuration*/
  
    u8FoodState = 0;
    u8DoorState = 0;
    
    u8HeatState = APP_HEAT_OFF;
    
    SERVICES_vidExecWhenPressed(SERVICES_KEY_DEL, APP_vidRestartSystem);
    /*Setting variables used to track user input cursor*/
    u8CurrXPos = 0;
    u8CurrYPos = 1;
    u8UserTextIndex = 0;

    LCD_vidSendCommand(LCD_CLEAR_SCREEN);
    LCD_vidWriteString("Enter time: ");

    LCD_vidGoToXY(LCD_XPOS0, LCD_YPOS3);
    LCD_vidWriteString("*: Del, #: Enter");

    /*Setting cursor to user input position*/
    LCD_vidGoToXY(LCD_XPOS0, LCD_YPOS1);

    /*Allow keyboard to be on*/
    u8KeyboardState = 1;
}

/*Function to convert user input into minutes(decimal value)
 *that can be added and subtracted
 */
void APP_vidConvertToTime(u8 u8UserTextEnd) {
    switch (u8UserTextEnd) {
        case 3:
            u16Seconds = (u8UserInput[0] - '0')*100;
            u16Seconds = (u8UserInput[1] - '0')*10;
            u16Seconds = (u8UserInput[1] - '0');
        case 2:
            u16Seconds = (u8UserInput[0] - '0')*10;
            u16Seconds += u8UserInput[1] - '0';
            break;
        case 1:
            u16Seconds = u8UserInput[0] - '0';
            break;
        default:
            LCD_vidWriteNumber(u16Seconds);
            break;
    }

}

void APP_vidCountOVF(void) {
    u8TimeEntered = 0;
    u16OVFCount++;
    if (u16OVFCount == 3812) {
        u16OVFCount = 0;
        u16Seconds--;
        LCD_vidGoToXY(LCD_XPOS12, LCD_YPOS0);
        LCD_vidWriteNumber(u16Seconds);
        if (u16Seconds == 0) {
                u8HeatState = APP_HEAT_OFF;

            /*Turn-off LED*/
            DIO_vidSetPinValue(DIO_PORTC, DIO_PIN7, STD_LOW);
            APP_vidControlHeating(APP_HEAT_OFF);
            /*Restarting system will disable timer interrupt*/
            APP_vidRestartSystem();
        }
    }
}

void APP_vidTestText(void) {
    u8 i = 0;
    LCD_vidGoToXY(LCD_XPOS0, LCD_YPOS2);
    /*In case of no user input*/
    if (u8UserTextEnd == 0) {
        LCD_vidClearLine(LCD_YPOS2);
        LCD_vidGoToXY(LCD_XPOS0, LCD_YPOS2);
        LCD_vidWriteString("No time set");
        LCD_vidGoToXY(LCD_XPOS0, LCD_YPOS1);
        __delay_ms(1000);
        APP_vidRestartSystem();
    }        /*In case of user input*/
    else {
        /*Variable will be put elsewhere*/
        LCD_vidGoToXY(LCD_XPOS12, LCD_YPOS2);

        for (i = 0; i < u8UserTextEnd; i++) {
            LCD_vidWriteCharacter(u8UserInput[i]);
        }
        u8TimeEntered = 1;
        u8KeyboardState = 0;
    }
}

void APP_vidStartHeating(void) {

    u8HeatState = APP_HEAT_ON;
    APP_vidConvertToTime(u8UserTextEnd);

    /*Clear screen to show heating notification*/
    LCD_vidSendCommand(LCD_CLEAR_SCREEN);
    LCD_vidWriteString("Heating...");

    LCD_vidGoToXY(LCD_XPOS12,LCD_YPOS0);
    /*Writing the first second*/
    LCD_vidWriteNumber(u16Seconds);

    LCD_vidGoToXY(LCD_XPOS0, LCD_YPOS2);
    LCD_vidWriteString("RB4: Open door");

    LCD_vidGoToXY(LCD_XPOS0, LCD_YPOS3);
    LCD_vidWriteString("RA5: Cancel");
    /*Turn motor on*/
    DIO_vidSetPinValue(APP_LAMP_PORT, APP_LAMP_PIN, STD_HIGH);
    APP_vidControlHeating(APP_HEAT_ON);

    /*Start timer*/
    INTERRUPTS_vidEnableInterrupt(INTERRUPTS_TIMER0_OVF);
    INTERRUPTS_vidPutISR(INTERRUPTS_TIMER0_OVF,APP_vidCountOVF);
    INTERRUPTS_vidEnablePeripheralInterrupt();

}

void APP_vidChangeKeyboardState(void) {
    u8KeyboardState = 0;
    APP_vidTestText();
}

void APP_vidCheckWhileHeating(void) {
    if (DIO_u8GetPinValue(APP_DOOR_PORT, APP_DOOR_PIN) == APP_DOOR_OPEN) {
        /*To stop heating immediately*/
        APP_vidControlHeating(APP_HEAT_OFF);
        LCD_vidSendCommand(LCD_CLEAR_SCREEN);
        LCD_vidWriteString("Door opened");
        __delay_ms(1000);
        APP_vidRestartSystem();
    }
    if (DIO_u8GetPinValue(APP_CANCEL_PORT, APP_CANCEL_PIN) == APP_CANCEL_PRESSED) {
        APP_vidControlHeating(APP_HEAT_OFF);
        LCD_vidSendCommand(LCD_CLEAR_SCREEN);
        LCD_vidWriteString("Heating canceled");
        __delay_ms(1000);
        APP_vidRestartSystem();
    }

}

u8 APP_u8CheckToStart(void) 
{
    if (DIO_u8GetPinValue(APP_WEIGHT_PORT, APP_WEIGHT_PIN) == 1) {
        LCD_vidGoToXY(LCD_XPOS4, LCD_YPOS2);
        LCD_vidWriteString("Food");
        u8FoodState = 0;
    } else {
        LCD_vidDeleteFrom(LCD_XPOS4, LCD_YPOS2, 4);
        u8FoodState = 1;
        while (1) {
            if (DIO_u8GetPinValue(APP_DOOR_PORT, APP_DOOR_PIN) == 1) {

                LCD_vidGoToXY(LCD_XPOS0, LCD_YPOS2);
                LCD_vidWriteString("Door");
                u8DoorState = 0;
            } else {
                LCD_vidDeleteFrom(LCD_XPOS0, LCD_YPOS2, 4);
                u8DoorState = 1;
                break;
            }
        }
    }
    
    /*Check cancel button*/
    if (DIO_u8GetPinValue(APP_CANCEL_PORT,APP_CANCEL_PIN) == APP_CANCEL_PRESSED)
    {
        APP_vidRestartSystem();
    }
    
    if (u8FoodState && u8DoorState) {
        return 1;
    }
    {
        return 0;
    }
}

void APP_vidControlHeating(u8 u8Command) {
    if (u8Command == APP_HEAT_ON) {
        DIO_vidSetPinValue(APP_MOTOR_PORT, APP_MOTOR_PIN, STD_HIGH);
    } else {
        /*Disable running timer*/
        INTERRUPTS_vidDisableGlobalInterrupt();
        INTERRUPTS_vidDisableInterrupt(INTERRUPTS_TIMER0_OVF);
        DIO_vidSetPinValue(APP_MOTOR_PORT, APP_MOTOR_PIN, STD_LOW);
        INTERRUPTS_vidEnableGlobalInterrupt();
    }

}

u8 APP_u8CheckDoor(void)
{
  
    if (DIO_u8GetPinValue(APP_DOOR_PORT,APP_DOOR_PIN) == 0)
    {
        if (u8DoorState == 0)
        {
            LCD_vidDeleteFrom(LCD_XPOS0, LCD_YPOS2, 4);
            u8DoorState = 1;
            return 1;
        }
        else {
            LCD_vidGoToXY(LCD_XPOS0, LCD_YPOS2);
            LCD_vidWriteString("Door");
            u8DoorState = 0;
            return 0;
        }
    }
}

u8 APP_u8CheckFood(void)
{
    if (DIO_u8GetPinValue(APP_WEIGHT_PORT,APP_WEIGHT_PIN) == 0)
    {
        if (u8FoodState == 0)
        {
        LCD_vidDeleteFrom(LCD_XPOS5, LCD_YPOS2, 4);
        u8FoodState = 1;
        return 1;
        }
        else
        {
        LCD_vidGoToXY(LCD_XPOS5, LCD_YPOS2);
        LCD_vidWriteString("Food");
        u8FoodState = 0;
        return 0;
        }
    }
}

u8 APP_u8CheckStart(void)
{
    if (DIO_u8GetPinValue(APP_START_PORT,APP_START_PIN) == APP_START_PRESSED)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}