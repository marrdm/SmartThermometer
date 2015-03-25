/*
 * SPI.h
 *
 *  Created on: Mar 19, 2015
 *      Author: jeffrey
 */

#ifndef SPI_H_
#define SPI_H_

#define lcd 0b0000
#define sd 	0b0100
#define rtc 0b1000
#define ext 0b1100

#include "Software.h"

void SPI_init();
void lcd_init();
void delayUS(int microSecs);
void delayMS(int milliSecs);
void SPISend(char device, char display);



#endif /* SPI_H_ */
