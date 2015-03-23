/*
 * adc.h
 *
 *  Created on: 23 Mar 2015
 *      Author: Marcus
 */

#ifndef ADC_H_
#define ADC_H_

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include "uart.h"
#include "str.h"
#include "temp.h"

#define N_SAMPLES 100000

void adc_init();

#endif /* ADC_H_ */
