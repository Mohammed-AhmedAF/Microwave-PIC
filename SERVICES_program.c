#include "Macros.h"
#include "Std_Types.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "SERVICES_interface.h"
#include "APP_interface.h"
#include <xc.h>

u8 u8keyPressed = 0xFF;

#define _XTAL_FREQ 4000000
u8 u8UserTextIndex = 0;

/*Global variable for current x-y position of keypad*/
u8 u8CurrXPos, u8CurrYPos = 1;
u8 u8UserTextEnd, u8StartOfText = 0;
extern u8 u8RestartSys;
u8 u8UserInput[10];

/*Pointer to the function to be executed when Enter key is pressed*/
void (*ptrFunc[2]) (void);

void SERVICES_delay_ms(u16 u16delayValue)
{
    u16 u16i, u16x;
    for (u16i = 0; u16i < u16delayValue; u16i++)
    {
        for(u16x = 0; u16x < 600; u16x++);
    }
}

/*Assign functions to be executed when certain keys are pressed*/
void SERVICES_vidExecWhenPressed(u8 u8Key, void (*pf) (void))
{
    ptrFunc[u8Key] = pf;
}

u8 SERVICES_u8WriteCharacter(void) {
	do {
		u8keyPressed = KEYPAD_u8GetKey();
		__delay_ms(30);
        u8keyPressed = KEYPAD_u8GetKey();
	}while(u8keyPressed == 0xFF);
	if (u8keyPressed == KEYPAD_DELETE) {
		SERVICES_delay_ms(10);
        ptrFunc[SERVICES_KEY_DEL]();
	}
    else if (u8keyPressed == KEYPAD_ENTER)
    {
        u8UserTextEnd = u8CurrXPos-u8StartOfText;
        ptrFunc[SERVICES_KEY_ENTER]();
    }
	else {
		if((u8keyPressed >= 0) && (u8keyPressed <= 9)) {
			u8keyPressed += 0x30;
		}
         LCD_vidWriteCharacter(u8keyPressed);
         u8CurrXPos++;
         u8UserInput[u8UserTextIndex] = u8keyPressed;
         u8UserTextIndex++;

         return u8keyPressed;
         
	}
   
}

u8 SERVICES_vidDeleteCharacter(u8 u8StartOfText)
{
    u8CurrXPos--;
    if (u8CurrXPos >= u8StartOfText && (u8CurrXPos < 20))
    {
        LCD_vidGoToXY(u8CurrXPos,u8CurrYPos);
        LCD_vidWriteCharacter(' ');
        /*The cursor position has moved automatically
         *to the next position, so it is got back to
         * the position of the space
         */
        LCD_vidGoToXY(u8CurrXPos,u8CurrYPos);
        return u8CurrXPos;
    }
    else {
        u8CurrXPos = 0;
        LCD_vidGoToXY(u8CurrXPos,u8CurrYPos);

    }
}

