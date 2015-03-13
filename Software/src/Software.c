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
void cycle_colour();

int main(void) {


	LPC_IOCON->R_PIO1_2 = 1;
	LPC_IOCON->R_PIO0_11 = 1;
	LPC_GPIO1->DIR |= (1<<2);
	LPC_GPIO0->DIR |= (1<<11);

	pwm_init();

    while(1) {
    	int i = 0;
    	while(i<10000){
    		i++;
    	}
    	cycle_colour();
    }
    return 0 ;
}

void cycle_colour(){
	static int colour = 255;
	static int colour_inc = 1;

	colour += colour_inc;
	pwm_red(colour - 255);
	pwm_blue(255 - colour);
	pwm_green(255 - (colour/2));

	if(colour > 511 || colour <= 0){
		colour_inc = - colour_inc;
	}
}
