/*
 * pwm.h
 *
 *  Created on: 5 Mar 2015
 *      Author: Marcus
 */

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

void pwm_init();
void pwm_red(int value);
void pwm_green(int value);
void pwm_blue(int value);
