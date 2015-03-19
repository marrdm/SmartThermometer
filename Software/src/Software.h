/*
 * Software.h
 *
 *  Created on: 5 Mar 2015
 *      Author: Marcus
 */

#ifndef SOFTWARE_H_
#define SOFTWARE_H_

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include <cr_section_macros.h>

#include "pwm.h"
#include "uart.h"

#define SYSTEM_OSCILLATOR 0		//
#define MAIN_CLOCK 0				//
#define SYSTEM_CLOCK 12000000		// 12MHz

#endif /* SOFTWARE_H_ */
