/*
 * uart.h
 *
 *  Created on: 13 Mar 2015
 *      Author: Marcus
 */


#ifndef UART_H_
#define UART_H_

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#define UART_TX_BUB_SIZE 32


void uart_init();
int uart_send(char str[], int len);
void uart_transmit();


#endif /* UART_H_ */
