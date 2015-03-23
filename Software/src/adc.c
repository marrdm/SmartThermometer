/*
 * adc.c
 *
 *  Created on: 23 Mar 2015
 *      Author: Marcus
 */

#include "adc.h"

void adc_init(){

	LPC_GPIO2->DIR |= (1<<6);					//ADC set up code
	LPC_GPIO2->DATA |= (1<<6);
	LPC_IOCON->PIO1_11 |= 1;					//table 94
	LPC_IOCON->PIO1_11 &= ~(1<<7);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);
	LPC_ADC->CR |= (1<<7)|(10<<8);				//channel 7, software controlled, 4.36MHz
	LPC_SYSCON->PDRUNCFG &= ~(1<<4);			//ADC powered up
	LPC_ADC->INTEN |= (1<<7);					//channel 7 interrupt enabled

	NVIC_SetPriority(ADC_IRQn, 1);					//enable ADC interrupt
	NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_IRQHandler (void){
	static int n = 0;
	static int sum = 0;
	int tmp = 0;
	tmp = LPC_ADC->GDR;
	tmp = tmp & (0x3ff<<6);
	tmp = tmp>>6;
	sum = sum + tmp;
	if(n<N_SAMPLES){
	LPC_ADC->CR |= (1<<24);//start conversion
	LPC_ADC->CR &= ~(1<<24);
	n++;
	}
	else {
		float average = (float) sum/N_SAMPLES;
		float voltage = average / 287;


		conv(average);
//		float temp_c = 247.456 - 0.4079 * average;
//
//		char temp_str[32];
//		int temp_len;
//
//		float2str(temp_c, 1, 32, temp_str, &temp_len);
//		uart_send(temp_str, temp_len);
//		uart_send("°C\r\n", 5);


		sum = 0;
		n = 0;
	}
}
