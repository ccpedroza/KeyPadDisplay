/*
 * SysTickInts.h
 *
 *  Created on: May 14, 2024
 *      Author: Crispy
 */

#ifndef __SYSTICKINTS_H__
#define __SYSTICKINTS_H__

// **************SysTick_Init*********************
// Initialize SysTick periodic interrupts
// Input: interrupt period
//        Units of period are 12.5ns (assuming 80 MHz clock)
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none
void SysTick_Init(uint32_t period);

uint32_t SysTick_Mailbox();
uint32_t Systick_CheckFlag();
void flagclear();
void SysTick_Handler();
void setOutput(char arr[3],int size);
void setRead();
#endif
