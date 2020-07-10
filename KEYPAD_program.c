#include <xc.h>
#include "Macros.h"
#include "Std_Types.h"
#include "KEYPAD_interface.h"
#include "DIO_interface.h"

#define _XTAL_FREQ 4000000

void KEYPAD_vidInit(void) {

	DIO_vidSetPinDirection(ROW0_PORT,ROW0_PIN,DIO_INPUT);
	DIO_vidSetPinDirection(ROW1_PORT,ROW1_PIN,DIO_INPUT);
	DIO_vidSetPinDirection(ROW2_PORT,ROW2_PIN,DIO_INPUT);
	DIO_vidSetPinDirection(ROW3_PORT,ROW3_PIN,DIO_INPUT);

    DIO_vidSetPinValue(ROW0_PORT,ROW0_PIN,STD_HIGH);
    DIO_vidSetPinValue(ROW0_PORT,ROW0_PIN,STD_HIGH);
    DIO_vidSetPinValue(ROW0_PORT,ROW0_PIN,STD_HIGH);
    DIO_vidSetPinValue(ROW0_PORT,ROW0_PIN,STD_HIGH);
    
	DIO_vidSetPinDirection(COL0_PORT,COL0_PIN,DIO_OUTPUT);
	DIO_vidSetPinDirection(COL1_PORT,COL1_PIN,DIO_OUTPUT);
	DIO_vidSetPinDirection(COL2_PORT,COL2_PIN,DIO_OUTPUT);

}

u8 keys[4][3] = {{'#',0,'*'},{9,8,7},{6,5,4},{3,2,1}};
u8 values[4] = {0x0E,0x0D,0x0B,0x07};
u8 colValues[3] = {0x06,0x05,0x03};
u8 value,i = 0;

u8 KEYPAD_u8GetKey(void) {
    u8 j;
	for (i = 0; i < 3; i++) {
         __delay_us(50) ;

		u8 x = 0;
		value = colValues[i];
		DIO_vidSetPinValue(COL0_PORT,COL0_PIN,GET_BIT(value,0));
		DIO_vidSetPinValue(COL1_PORT,COL1_PIN,GET_BIT(value,1));
		DIO_vidSetPinValue(COL2_PORT,COL2_PIN,GET_BIT(value,2));

		/*Rows Listening for low value */
		for(j =0; j<4;j++)
		{ 
            /*to avoid bouncing of keypad */
            __delay_us(50) ;
           
			if(!(PORTD & (1<<j)))//check if key is pressed
			{
                /*wait for key to be released  (Single press) */
				while(!(PORTD & (1<<j))); 
				switch(i)
				{
                    // first column RB0
				case(0):
                	{
					if (j == 0)return '*'; // first row RD0
					else if (j == 1) return '7';// second row 
					else if (j == 2) return '4';// third row 
					else if (j == 3) return '1';// fourth row 
					break;
                	}
                // second column RB1
				case(1):
                	{
					if (j == 0) return '0';// first row RD0 
					else if (j == 1) return '8';//second row 
					else if (j == 2) return '5';// third row 
					else if (j == 3) return '2';// fourth row 
					break;
                	}
                // third column RB2
				case(2):
                	{
					if (j == 0) return '#';// first row RD0
					else  if (j == 1) return '9';// second row RD1 
					else if (j == 2) return '6';// third row RD2
					else if (j == 3) return '3';//fourth row RD3
					break;
                	}
				
				}
			}
		}
	}
	return 0xFF;//Return 'A' if no key is pressed.
}


