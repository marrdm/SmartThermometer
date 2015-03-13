/*
 * uart.c
 *
 *  Created on: 13 Mar 2015
 *      Author: Marcus
 */

int uart_tx_buf_size = 32;
int uart_tx_buf_start = 0;
int uart_tx_buf_end = 0;
char uart_tx_buf[uart_tx_buf_size];

int uart_tx_active = 0;


int uart_send(char str[], int len){
/*
 * Return value n > 0 indicates a buffer overflow where n is the number of characters not entered into the buffer.
 */
	int i = 0;
	while(i < len){

		if( ((uart_tx_buf_end + 1) == uart_tx_buf_start) ||
				( (uart_tx_buf_end == (uart_tx_buf_size - 1) && (uart_tx_buf_start == 0) ))){
			break;									// Buffer full
		}
		if(uart_tx_buf_end == (uart_tx_buf_size - 1) ){
			uart_tx_buf_end = 0;
		}else{
			uart_tx_buf_end++;
		}

		uart_tx_buf[uart_tx_buf_end] = str[i];
		i++;

	}

	if(!uart_tx_active){
		uart_transmit();
	}
	return (len - i);
}

void uart_transmit(){
	if(uart_tx_buf_end == uart_tx_buf_start){
		uart_tx_active = 0;
		return;
	}

}
