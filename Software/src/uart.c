/*
 * uart.c
 *
 *  Created on: 13 Mar 2015
 *      Author: Marcus
 */

#include "uart.h"

int uart_tx_buf_start = 0;
int uart_tx_buf_end = 0;
char uart_tx_buf[UART_TX_BUB_SIZE];

int uart_tx_active = 0;

void uart_init(){
	LPC_IOCON->PIO1_7 |= 1;									//UART Initialization
	LPC_IOCON->PIO1_6 |= 1;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
	LPC_SYSCON->UARTCLKDIV = 156;
	LPC_UART->LCR = 0b11;
	LPC_UART->FCR = 0x7;
	LPC_UART->IER |= 1;
	LPC_UART->IER |= (1<<1);

	NVIC_SetPriority(UART_IRQn, 1);
	NVIC_EnableIRQ(UART_IRQn);


}

int uart_send(char str[], int len){
/*
 * Return value n > 0 indicates a buffer overflow where n is the number of characters not entered into the buffer.
 */
	NVIC_DisableIRQ(UART_IRQn);

	int i = 0;
	while(i < len){

		if( ((uart_tx_buf_end + 1) == uart_tx_buf_start) ||
				( (uart_tx_buf_end == (UART_TX_BUB_SIZE - 1) && (uart_tx_buf_start == 0) ))){
			break;									// Buffer full
		}

		uart_tx_buf[uart_tx_buf_end] = str[i];
		i++;

		if(uart_tx_buf_end == (UART_TX_BUB_SIZE - 1) ){
			uart_tx_buf_end = 0;
		}else{
			uart_tx_buf_end++;
		}
	}

	if(!uart_tx_active){
		uart_transmit();
	}
	NVIC_EnableIRQ(UART_IRQn);
	return (len - i);
}

void uart_transmit(){
	if(uart_tx_buf_end == uart_tx_buf_start){
		uart_tx_active = 0;
		return;
	}
	uart_tx_active = 1;
	LPC_UART->THR = uart_tx_buf[uart_tx_buf_start];

	if(uart_tx_buf_start == (UART_TX_BUB_SIZE - 1) ){
		uart_tx_buf_start = 0;
	}else{
		uart_tx_buf_start++;
	}

}

void UART_IRQHandler (void){
	int intid = LPC_UART->IIR;
	intid = (intid >> 1) & 0x7;

	if(intid == 2){		//Receive Data Available
		char c = LPC_UART->RBR;
		if(c == '\r'){
			uart_send("\r\n", 2);
		} else{
			uart_send(&c, 1);
		}
	}else if(intid == 1){		//Transmit Holding Register Empty
		uart_transmit();
	}

}
