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

float voltage = 0;								//global variables for calculating average voltage
int temp = 0;
int k = 0;
int sum = 0;
int i = 0;
char string[16];

void parser(char str[], int len);

void TIMER16_0_IRQHandler (void);
void UART_IRQHandler (void);
void PIOINT1_IRQHandler (void);
void ADC_IRQHandler (void);

int main(void) {
												//timer 16B0 setup code
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
	LPC_TMR16B0->MCR |= 0b11;
	LPC_TMR16B0->PR = 48 - 1;
	LPC_TMR16B0->MR0 = 1*1000 * 1000 * 2 - 1;		//interrupt every 2 seconds
	LPC_TMR16B0->TCR = 2;
	LPC_TMR16B0->TCR = 1;

	LPC_IOCON->R_PIO1_2 = 1;
	LPC_IOCON->R_PIO0_11 = 1;
	LPC_GPIO1->DIR |= (1<<2);
	LPC_GPIO0->DIR |= (1<<11);
												//button initialization code
	LPC_GPIO1->DIR &= ~(1<<4);
	LPC_GPIO1->IS &= ~(1<<4);					//edge sensitive
	LPC_GPIO1->IBE &= ~(1<<4);					// trigger interrupt only on one edge
	LPC_GPIO1->IEV &= ~(1<<4);					//trigger on falling edge
	LPC_GPIO1->IE |= (1<<4);					//enable interrupt

	LPC_GPIO2->DIR |= (1<<6);					//ADC set up code
	LPC_GPIO2->DATA |= (1<<6);
	LPC_IOCON->PIO1_11 |= 1;					//table 94
	LPC_IOCON->PIO1_11 &= ~(1<<7);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);
	LPC_ADC->CR |= (1<<7)|(10<<8);				//channel 7, software controlled, 4.36MHz
	LPC_SYSCON->PDRUNCFG &= ~(1<<4);			//ADC powered up
	LPC_ADC->INTEN |= (1<<7);					//channel 7 interrupt enabled

												//SPI set up code
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<18);
	LPC_IOCON->PIO2_1 = 2;						//table 66, SCK1
	LPC_IOCON->PIO2_0 = 2;						//table 107, SSEL1
	LPC_IOCON->PIO2_2 = 2;						//table 127. MISO1
	LPC_IOCON->PIO2_3 = 2;						//table 139, MOSI1
	LPC_SYSCON->SSP1CLKDIV |= 48;				//table 24, SCK1 is set to 1 MHz
	LPC_SYSCON->PRESETCTRL = 1 | (1<<2);		//de-asserts reset signal

	//pwm_init();
	uart_init();


	__disable_irq();
	NVIC_SetPriority(TIMER_16_0_IRQn, 0);		//enable timer interrupt
	NVIC_EnableIRQ(TIMER_16_0_IRQn);
	NVIC_SetPriority(UART_IRQn, 0);				//enable UART interrupt
	NVIC_EnableIRQ(UART_IRQn);
	NVIC_SetPriority(UART_IRQn, 0);				//enable UART interrupt
	NVIC_EnableIRQ(UART_IRQn);
	NVIC_SetPriority(EINT1_IRQn, 0);			//enable external interrupt
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_SetPriority(ADC_IRQn, 0);					//enable ADC interrupt
	NVIC_EnableIRQ(ADC_IRQn);
	__enable_irq();								//enable all interrupts

    while(1) {
    	int i = 0;
    	while(i<10000){
    		i++;
    	}
    	//cycle_colour();
    }
    return 0 ;
}

/*void cycle_colour(){
	static int colour = 255;
	static int colour_inc = 1;

	colour += colour_inc;
	pwm_red(colour - 255);
	pwm_blue(255 - colour);
	pwm_green(255 - (colour/2));

	if(colour > 511 || colour <= 0){
		colour_inc = - colour_inc;
	}
}*/

void parser(char str[], int len){
	/*
	char short_str[16];
	int short_len = 0;
	int i = 0;

	int blink_val;

	if(len >= 16){
		UART_send("ERROR, string too long! \n\r", 26);
		return;
	}
	while(i<len){
		if(str[i] != ' '){
			short_str[short_len] = str[i];
			short_len++;
		}
		i++;
	}

	i = 0;
	while(i<short_len){
		if(short_str[i] != command_on[i]){
			break;
		}
		if(i == 2){
			on();
			UART_send("Status on \r\n", 12);
			return;
		}
		i++;
	}

	i = 0;
	while(i<short_len){
		if(short_str[i] != command_off[i]){
			break;
		}
		if(i == 3){
			off();
			UART_send("Status off \r\n", 13);
			return;
		}
		i++;
	}

	i = 0;
	while(i<len){
		if(short_str[i] != command_blink[i]){
			break;
		}
		if(i == 4){
			if(str2int(&short_str[5], short_len - 6, &blink_val) == 0){
				if(blink_val > 0){
					blink(blink_val, -1);

					UART_send("status blink: ", 15);
					UART_send(&short_str[5], short_len - 6);
					UART_send("\r\n", 2);

					return;
				}
			}


		}
		i++;
	}
	UART_send("ERROR, could not parse:\t", 24);
	UART_send(str, len);
	UART_send("\n", 1);
	*/
}

void TIMER16_0_IRQHandler (void){
	LPC_TMR16B0->IR = 1;
	LPC_ADC->CR |= (1<<24);	//start AD conversion'
	LPC_ADC->CR &= ~(1<<24);

}



void PIOINT1_IRQHandler (void){
	 LPC_GPIO1->IC |= (1<<4);				//reset interrupt flag

}

void ADC_IRQHandler (void){
	int temp = 0;
	temp = LPC_ADC->GDR;
	temp = temp & (0x3ff<<6);
	temp = temp>>6;
	sum = sum + temp;
	if(k<1000){
	LPC_ADC->CR |= (1<<24);//start conversion
	LPC_ADC->CR &= ~(1<<24);
	k++;
	}
	else {
	k = 0;
	voltage = sum/1000;
    voltage /= 287;
    sum = 0;
    k = 0;
	}
}



