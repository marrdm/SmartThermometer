/*
 * pwm.h
 *
 *  Created on: 5 Mar 2015
 *      Author: Marcus
 */

#ifndef PWM_H_
#define PWM_H_

#include "Software.h"

void pwm_init();
void pwm_red(int value);
void pwm_green(int value);
void pwm_blue(int value);

#endif /* PWM_H_ */
