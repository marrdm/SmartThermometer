/*
 * pwm.c
 *
 *  Created on: 5 Mar 2015
 *      Author: Marcus
 */

#include "pwm.h"

void pwm_init(LPC_TMR_TypeDef timer, int frequency, int reset_channel){
//	int prescale = SYSTEM_CLOCK / (frequency * 1000);
/*
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);		//Power up tmr0
	LPC_IOCON->R_PIO1_1 = 3;

	timer->PR = 28;//prescale;
	timer->MCR |= (1<<10);
	timer->MR3 = 255;
	timer->MR0 = 128;

	timer->PWMC = 1;

	timer->TCR = 0x2;		//Reset timer
	timer->TCR = 0x1;		//Start timer
*/
}

void pwm_enable_output(int channel){

}
