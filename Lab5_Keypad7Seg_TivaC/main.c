

/**
 * main.c
 */
#include <stdint.h>
#include "SevenSeg.h"
#include "Keypad.h"
#include "tm4c123gh6pm.h"
#include "SysTickInts.h"
#include "PLL.h"
#include "LCD.h"


char inputs[];
char inputstrue[];


void main(void){                          //OPEN MAIN
      PLL_Init(Bus80MHz);
       sevenseg_init();
       Keypad_Init();
       SysTick_Init(2000000);

       int i,keycounter=0;
       int size=0;
       char currentkey;
       while(1)
       {
           //delayMs(10);
           currentkey=getkey();


           if(currentkey=='#')
           {
               if(i>3)
               {
                   i=0;
               }
               else
               {
               int j=0;
               setRead();
               for(j=0;j<4;j++)
                   {
                   inputstrue[j]=inputs[j];
                   }
               setOutput(inputstrue,size);
               i=0;
               keycounter=0;
               size=0;
               }
           }
           else
           {
               if(i>3)
               {

                   i=0;
               }
               else
               {
                  inputs[i]=currentkey;
                  i++;
                  keycounter++;
                  size++;
               }
           }


       }


}
/*
int main(void) {
    const static unsigned char digitPattern[] = {0x98,0x80,0xF8,0x82,0x92,0x99,0xB0, 0xA4, 0xF9, 0xC0,};
    int i;


    sevenseg_init();    // initialize SSI2 that connects to the shift registers

    while(1) {
        SSI2_write(digitPattern[i]);    // write digit pattern to the seven segments
        SSI2_write((1 << i%4));           // select digit
        if (++i >3)
            i = 0;
        delayMs(1);                     // 1000 / 60 / 4 = 4.17
    }
}
*/
