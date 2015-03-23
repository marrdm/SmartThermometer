/*
 * SPI.c
 *
 *  Created on: Mar 19, 2015
 *      Author: jeffrey
 */

#include "SPI.h"

int uart_tx_buf_start = 0;


void SPI_init(){
	LPC_GPIO0->DIR |= (1<<2)|(1<<3);			//GPIO CS to deMux are configured as outputs
	LPC_GPIO0->DATA &= ~((1<<2)|(1<<3));		//set S0 S1 to 00
												//SPI set up code
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<18);
	LPC_IOCON->PIO2_1 = 2;						//table 66, SCK1
	LPC_IOCON->PIO2_0 = 2;						//table 107, SSEL1
	LPC_IOCON->PIO2_2 = 2;						//table 127. MISO1
	LPC_IOCON->PIO2_3 = 2;						//table 139, MOSI1
	LPC_SYSCON->SSP1CLKDIV |= 48;				//table 24, SCK1 is set to 1 MHz
	LPC_SSP1->CR0 |= 0x7;						//8 bit mode
	LPC_SSP1->CPSR = 126;						//prescaler down from SPI_PCLK, 380 kHz
	LPC_SYSCON->PRESETCTRL = 1 | (1<<2);		//de-asserts reset signal
	LPC_SSP1->CR1 |= 2;							//enable SPI controller
	LPC_SSP1->DR;								//read write data register
}

void lcd_init(){
	LPC_IOCON->PIO2_2 = 0;
	LPC_GPIO2->DIR = (1<<2);
	LPC_GPIO2->DATA &= ~(1<<2);		//drive RS low
	delayMS(200);
	SPISend(0x38);					//function set
	delayUS(30);					//delay may not be needed
	SPISend(0x39);					//function set
	delayUS(30);
	SPISend(0x14);					//internal OSC frequency = 380 kHz, Bias for 3.3V
	delayUS(30);
	SPISend(0x78);					//Contrast set
	delayUS(30);
	SPISend(0x55);					//Power/ICOn/Contrast control
	delayUS(30);
	SPISend(0x6D);					//Follower control
	delayMS(200);
	SPISend(0x0C);					//Display on/off control
	delayUS(30);
	SPISend(0x01);
	delayMS(2);
	SPISend(0x06);
	delayUS(30);
}

void SPISend(char display){

}

void delayMS(int milliSecs){

}
