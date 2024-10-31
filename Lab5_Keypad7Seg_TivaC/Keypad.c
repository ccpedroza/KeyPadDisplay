/*
 * Keypad.c
 *
 *  Created on: May 13, 2024
 *      Author: Crispy
 */

//*********************************************************
//Title:    Keypad input to PORTB LED
//          Based on Example 12.4C                        *
//          HCS12 Microcontroller And Embedded Systems    *
//          Using Assembly and C with CodeWarrior         *
//          1st Edition                                   *
//          by Mazidi & Causey
//Modified and tested by Travis Chandler
//Platform: Wytec Dragon12 plus Dev board                 *
//Compiler: Feescale CodeWarrior IDE v5.9.0               *

//*********************************************************
//On Dragon12+ board, the rows and columns of 4x4 keypad are connected to PORTA.
//See page 26 of Dragon12+ User's Manual
//As you press any key the ASCII value for the key is placed on the LEDs of PORTB
#include<stdint.h>
#include "tm4c123gh6pm.h"      /* common defines and macros */

#include "Keypad.h"

const unsigned char keypads[4][4] =
{
'1','2','3','A',
'4','5','6','B',
'7','8','9','C',
'*','0','#','D'
};
const unsigned char keypad[4][4]=
{
0xF9,0xA4,0xB0,'A',
0x99,0x92,0x82,'B',
0xF8,0x80,0x90,'C',
'*',0xC0,'#','D'
};

/**************MAIN*******************************/
                    //CLOSE MAIN
void Keypad_Init(void)
{
        SYSCTL_RCGCGPIO_R|=0x09;
        //rows
        while((SYSCTL_RCGCGPIO_R)&0x09==0);
        GPIO_PORTD_PCTL_R &=0x00FFFFFF;
        GPIO_PORTA_PCTL_R &=0x00FFFFFF;

        GPIO_PORTA_CR_R |= 0x3C;
        GPIO_PORTD_CR_R |= 0x0F;

        GPIO_PORTA_AMSEL_R &= ~0x3C;
        GPIO_PORTA_AFSEL_R &= ~0x3C; // Clear bits 2-5 to disable alternate functions

        GPIO_PORTD_AFSEL_R &= ~0x0F; // Clear bits 0-3 to disable alternate functions
        GPIO_PORTD_AMSEL_R &= ~0x0F; // Clear bits 0-3 to disable analog functionality

        GPIO_PORTA_DIR_R |= 0x3C;  // Set bits 2-5 to set as outputs
        GPIO_PORTD_DIR_R &= ~0x0F; // Clear bits 0-3 to set as inputs


        GPIO_PORTA_PDR_R |= 0x3C;
        GPIO_PORTD_PDR_R |= 0x0F;

        GPIO_PORTA_DEN_R |= 0x3C;
        GPIO_PORTD_DEN_R |= 0x0F;  // Enable digital functionality on pins 0-3

        //columns







}
unsigned char column,row;
char getkey()
{
    int ii=0;
    char current;
while(1){                              //OPEN WHILE(1)
   do{                                 //OPEN do1
       GPIO_PORTA_DATA_R = GPIO_PORTA_DATA_R | 0x3C;            //COLUMNS SET HIGH
      row = GPIO_PORTD_DATA_R & 0x0F;              //READ ROWS
   }while(row == 0x00);                //WAIT UNTIL KEY PRESSED //CLOSE do1



   do{                                 //OPEN do2
      do{                              //OPEN do3
         mSDelay(1);                   //WAIT
         row = GPIO_PORTD_DATA_R & 0x0F;           //READ ROWS
      }while(row == 0x00);             //CHECK FOR KEY PRESS //CLOSE do3

      mSDelay(15);                     //WAIT FOR DEBOUNCE
      row = GPIO_PORTD_DATA_R & 0x0F;
   }while(row == 0x00);                //FALSE KEY PRESS //CLOSE do2

   while(1){                           //OPEN while(1)

       GPIO_PORTA_DATA_R &= 0xC3;                   //CLEAR COLUMN
       GPIO_PORTA_DATA_R |= 0x04;                   //COLUMN 0 SET HIGH
      row = GPIO_PORTD_DATA_R & 0x0F;              //READ ROWS
      if(row != 0x00){                 //KEY IS IN COLUMN 0
         column = 0;
         break;                        //BREAK OUT OF while(1)
      }
      GPIO_PORTA_DATA_R &= 0xC3;                   //CLEAR COLUMN
      GPIO_PORTA_DATA_R |= 0x08;                   //COLUMN 1 SET HIGH
      row = GPIO_PORTD_DATA_R & 0x0F;              //READ ROWS
      if(row != 0x00){                 //KEY IS IN COLUMN 1
         column = 1;
         break;                        //BREAK OUT OF while(1)
      }

      GPIO_PORTA_DATA_R &= ~0x3C;                   //CLEAR COLUMN
      GPIO_PORTA_DATA_R |= 0x10;                   //COLUMN 2 SET HIGH
      row = GPIO_PORTD_DATA_R & 0x0F;              //READ ROWS
      if(row != 0x00){                 //KEY IS IN COLUMN 2
         column = 2;
         break;                        //BREAK OUT OF while(1)
      }
      GPIO_PORTA_DATA_R &= ~0x3C;                   //CLEAR COLUMN
      GPIO_PORTA_DATA_R |= 0x20;                   //COLUMN 3 SET HIGH
      row = GPIO_PORTD_DATA_R & 0x0F;              //READ ROWS
      if(row != 0x00){                 //KEY IS IN COLUMN 3
         column = 3;


         break;                        //BREAK OUT OF while(1)
      }
      row = 0;                         //KEY NOT FOUND
   break;
   }
   if(row == 0x01)
   {
       current=keypad[0][column];

   }
   else if(row == 0x02)
   {
       current=keypad[1][column];

   }
   else if(row == 0x04)
   {
       current=keypad[2][column];

   }
   else if(row == 0x08)
   {
       current=keypad[3][column];

   }
   do{
      mSDelay(15);
      GPIO_PORTA_DATA_R = GPIO_PORTA_DATA_R | 0x3C;            //COLUMNS SET HIGH
      row = GPIO_PORTD_DATA_R & 0x0F;              //READ ROWS
   }while(row != 0x00);
   return current;
}
}
/**********************SUBROUTINES***********/

void mSDelay(unsigned int itime){
unsigned int i; unsigned int j;
   for(i=0;i<itime;i++)
      for(j=0;j<4000;j++);


}
