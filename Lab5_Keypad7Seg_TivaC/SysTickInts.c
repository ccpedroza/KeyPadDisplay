/*
 * SysTickInts.c
 *
 *  Created on: May 14, 2024
 *      Author: Crispy
 */
#include <stdint.h>
#include "PLL.h"
#include "SysTickInts.h"
#include "tm4c123gh6pm.h"
#include "SevenSeg.h"
#include "Keypad.h"
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
volatile uint32_t Counts;
uint32_t wait_per;

int iii=0;
int ready=0;
char outputs[]={0XFF,0XFF,0XFF,0XFF};
void SysTick_Init(uint32_t period) {
    long sr = StartCritical();
    wait_per = period;
    Counts = 0;
    NVIC_ST_CTRL_R = 0;                  // disable SysTick during setup
    NVIC_ST_RELOAD_R = period - 1;       // maximum reload value
    NVIC_ST_CURRENT_R = 0;               // any write to current clears it
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;  // priority 2
    NVIC_ST_CTRL_R = 0x00000007;         // enable SysTick with interrupts
    //int i=0;
    //for(i=0;i<4;i++)
    //{
        //outputs[i]=0xC0;
    //}
    EnableInterrupts();

    EndCritical(sr);
}
void SysTick_Handler()
{


    SSI2_write(outputs[iii]);

    // Select digit
    SSI2_write(1 << (iii % 4));

    // Increment iii and reset if it exceeds 3
    if (++iii >3) {
        iii = 0;

    }
    delayMs(5);
    }


void setOutput(char arr[],int size)
{
   switch(size)
   {
   case 4:
   {
        if(ready)
        {
            int i=0;
            for(i=0;i<4;i++)
            {
                outputs[i]=arr[3-i];
            }
            i=0;

        }
        break;
   }
   case 3:
   {
       if(ready)
       {
           int i=0;
           for(i=0;i<3;i++)
           {
               outputs[i]=arr[2-i];
           }
           i=0;
           outputs[3]=0xFF;
       }
       break;
   }
   case 2:
   {
       if(ready)
       {
           int i=0;
           for(i=0;i<2;i++)
           {
               outputs[i]=arr[1-i];
           }
           i=0;
           outputs[3]=0xFF;
           outputs[2]=0xFF;

       }
       break;
   }
   case 1:
   {
       if(ready)
       {
           int i=0;
           for(i=0;i<1;i++)
           {
               outputs[i]=arr[0-i];
           }
           i=0;
           outputs[3]=0xFF;
           outputs[2]=0xFF;
           outputs[1]=0xFF;
       }
       break;
   }
   default:
   {
       break;
   }
   }
   }

void setRead()
{
    ready=1;
}
/*void SysTick_Handler()
{

    if(ready)
    {
    SSI2_write(outputs[iii]);    // write digit pattern to the seven segments
    SSI2_write((1 << iii%4));           // select digit
    if (++iii >3)
    iii = 0;
    delayMs(4);                     // 1000


    }
}
*/
