/*
 * SPI.h
 *
 *  Created on: Mar 19, 2015
 *      Author: jeffrey
 */

#ifndef SPI_H_
#define SPI_H_

#include "Software.h"

void lcd_init();
void delayUS(int microSecs);
void delayMS(int milliSecs);
void SPISend(char display);



#endif /* SPI_H_ */