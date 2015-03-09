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

	pwm_init();

	int k = 1;
	int j = 0;
    while(1) {
    	int i = 0;
    	while(i<10000){
    		i++;
    	}
    	j = j + k;
    	pwm_red(j);
//    	pwm_blue(j);
    	pwm_green(255 - j);
    	if(j > 255 || j <= 0){
    		k = - k;
    	}
    }
    return 0 ;
}
