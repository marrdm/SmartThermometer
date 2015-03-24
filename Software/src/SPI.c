/*
 * SPI.c
 *
 *  Created on: Mar 19, 2015
 *      Author: jeffrey
 */

#include "SPI.h"

#define lcd 0b0000
#define sd 	0b0100
#define rtc 0b1000
#define ext 0b1100

void SPI_init(){

	LPC_SYSCON->PRESETCTRL |= (1<<2);		//de-asserts reset signal

	LPC_GPIO0->DIR |= (1<<2)|(1<<3);			//GPIO CS to deMux are configured as outputs
	LPC_GPIO0->DATA &= ~((1<<2)|(1<<3));		//set S0 S1 to 00
												//SPI set up code
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<18);
	LPC_IOCON->PIO2_1 |= 2;						//table 66, SCK1
	LPC_IOCON->PIO2_0 |= 2;						//table 107, SSEL1
	LPC_IOCON->PIO2_2 |= 2;						//table 127. MISO1
	LPC_IOCON->PIO2_3 |= 2;						//table 139, MOSI1
	LPC_SYSCON->SSP1CLKDIV |= 48;				//table 24, SCK1 is set to 1 MHz
	LPC_SSP1->CR0 |= 0x7;						//8 bit mode
	LPC_SSP1->CPSR = 126;						//prescaler down from SPI_PCLK, 380 kHz
	LPC_SYSCON->PRESETCTRL |= (1<<2);		//de-asserts reset signal
	LPC_SSP1->CR1 |= 2;							//enable SPI controller


}

void lcd_init(){
	LPC_IOCON->PIO2_2 = 0;
	LPC_GPIO2->DIR = (1<<2);
	LPC_GPIO2->DATA &= ~(1<<2);		//drive RS low
	delayMS(200);
	SPISend(lcd, 0x38);					//function set
	delayMS(2);						//delay may not be needed
	SPISend(lcd, 0x39);					//function set
	delayMS(2);
	SPISend(lcd, 0x14);					//internal OSC frequency = 380 kHz, Bias for 3.3V
	delayMS(2);
	SPISend(lcd, 0x78);					//Contrast set
	delayMS(2);
	SPISend(lcd, 0x55);					//Power/ICOn/Contrast control
	delayMS(2);;
	SPISend(lcd, 0x6D);					//Follower control
	delayMS(200);
	SPISend(lcd, 0x0C);					//Display on/off control
	delayMS(2);
	SPISend(lcd, 0x01);
	delayMS(20);
	SPISend(lcd, 0x06);
	delayMS(2);
}

void SPISend(char device, char display){
	LPC_GPIO2->DATA &= ~(device);
	LPC_GPIO2->DATA |= device;			//set mux to select proper chip
	LPC_SSP1->DR = display;				//write data to send register
}

void delayMS(int milliSecs){
	int i = 0;
	while(i<milliSecs){
		if(LPC_TMR16B1->EMR & 1){		//wait until EM1 is high, this means it has been a millisecond
			LPC_TMR16B0->EMR &= ~(1<<1);	//set EM1 back low
			i++;
		}
	}
}
/*
void delayUS(int microSecs){
	int i = 0;
	while( i< microSecs) i++;
}
}
*/
