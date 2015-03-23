/*
 * pwm.c
 *
 *  Created on: 5 Mar 2015
 *      Author: Marcus
 */

#include "pwm.h"

//32B1_MAT0		RED
//32B1_MAT1		GREEN
//32B0_MAT3		BLUE

void pwm_init(){
	LPC_SYSCON->SYSAHBCLKCTRL |= (3<<9);		//Power up CT32B0 and CT32B0

	LPC_IOCON->R_PIO1_1 = 3;
	LPC_IOCON->R_PIO1_2 = 3;
	LPC_IOCON->R_PIO0_11 = 3;

	LPC_TMR32B1->PR = 28;						//set prescaler
	LPC_TMR32B1->MCR |= (1<<10);				//set timer to reset on MR3
	LPC_TMR32B1->MR3 = 255;
	LPC_TMR32B1->MR0 = 255;
	LPC_TMR32B1->MR1 = 255;

	LPC_TMR32B1->PWMC |= (1<<0);				//set MR0 as PWM output
	LPC_TMR32B1->PWMC |= (1<<1);				//set MR1 as PWM output

	LPC_TMR32B1->TCR = 0x2;						//Reset CT32B1
	LPC_TMR32B1->TCR = 0x1;						//Start CT32B1


	LPC_TMR32B0->PR = 28;						//set prescaler
	LPC_TMR32B0->MCR |= (1<<1);					//set timer to reset on MR0
	LPC_TMR32B0->MR0 = 255;
	LPC_TMR32B0->MR3 = 255;

	LPC_TMR32B0->PWMC |= (1<<3);				//set MR3 as PWM output

	LPC_TMR32B0->TCR = 0x2;						//Reset CT32B1
	LPC_TMR32B0->TCR = 0x1;						//Start CT32B1

	pwm_red(0);
	pwm_green(0);
	pwm_blue(0);
}

void pwm_red(int value){
	if(value < 0){
		value = 0;
	}else if(value > 255){
		value = 255;
	}
	LPC_TMR32B1->MR0 = 255 - value;
}

void pwm_green(int value){
	if(value < 0){
		value = 0;
	}else if(value > 255){
		value = 255;
	}
	LPC_TMR32B0->MR3 = 255 - value;
}

void pwm_blue(int value){
	if(value < 0){
		value = 0;
	}else if(value > 255){
		value = 255;
	}
	LPC_TMR32B1->MR1 = 255 - value;
}

