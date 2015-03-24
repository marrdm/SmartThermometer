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

char string[16];

void parser(char str[], int len);

void TIMER16_0_IRQHandler (void);
void UART_IRQHandler (void);
void PIOINT1_IRQHandler (void);
void ADC_IRQHandler (void);

int main(void) {
												//timer 16B0 setup code
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
	LPC_TMR16B0->MCR |= (0b11);//|(1<<4);
	LPC_TMR16B0->PR = 48 - 1;
	LPC_TMR16B0->MR0 = 1*1000 * 1000 * 2 - 1;	//interrupt every 2 seconds
	LPC_TMR16B0->TCR = 2;
	LPC_TMR16B0->TCR = 1;
												//timer 16B1 setup code
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8);
	LPC_TMR16B1->MCR |= 0b10;
	LPC_TMR16B1->PR = 48 - 1;					//reset on match on MRO, no interrupt
	LPC_TMR16B1->MR0 = 1000 - 1;				//interrupt every millisecond seconds
	LPC_TMR16B1->EMR = 2<<4;					//set EM1 high on match
	LPC_TMR16B1->TCR = 2;
	LPC_TMR16B1->TCR = 1;
												//button initialization code
	LPC_GPIO1->DIR &= ~(1<<4);
	LPC_GPIO1->IS &= ~(1<<4);					//edge sensitive
	LPC_GPIO1->IBE &= ~(1<<4);					// trigger interrupt only on one edge
	LPC_GPIO1->IEV &= ~(1<<4);					//trigger on falling edge
	LPC_GPIO1->IE |= (1<<4);					//enable interrupt


	


	__disable_irq();
	SPI_init();
//	lcd_init();
	NVIC_SetPriority(TIMER_16_0_IRQn, 1);		//enable timer interrupt
	NVIC_EnableIRQ(TIMER_16_0_IRQn);
	uart_init();
	pwm_init();
	NVIC_SetPriority(EINT1_IRQn, 0);			//enable external interrupt
	NVIC_EnableIRQ(EINT1_IRQn);
	adc_init();
	__enable_irq();								//enable all interrupts


    while(1) {
    	//while(i<10000){
    	//	i++;
    	//}
    	int v = 0x7E;
//    	LPC_SSP1->DR = v;
 //   	LPC_SSP1->DR = 73;
//    	for(i=0; i<0xFFFFF; i++);			//delay to make scope reading easier
    }
    return 0 ;
}


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
	switch_mode();
	uart_send("\r\n", 2);
	LPC_GPIO1->IC |= (1<<4);				//reset interrupt flag
}





