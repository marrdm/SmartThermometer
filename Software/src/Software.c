/*
===============================================================================
 Name        : Software.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "Software.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {


	LPC_IOCON->R_PIO1_2 = 1;
	LPC_IOCON->R_PIO0_11 = 1;
	LPC_GPIO1->DIR |= (1<<2);
	LPC_GPIO0->DIR |= (1<<11);

	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);		//Power up tmr0
	LPC_IOCON->R_PIO1_1 = 3;

	LPC_TMR32B1->PR = 28;
	LPC_TMR32B1->MCR |= (1<<10);
	LPC_TMR32B1->MR3 = 255;
	LPC_TMR32B1->MR0 = 256;

	LPC_TMR32B1->PWMC = (1<<0);
	LPC_TMR32B1->PWMC |= (1<<3);

	LPC_TMR32B1->TCR = 0x2;		//Reset timer
	LPC_TMR32B1->TCR = 0x1;		//Start timer


    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
