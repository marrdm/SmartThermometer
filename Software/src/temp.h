/*
 * temp.h
 *
 *  Created on: 23 Mar 2015
 *      Author: Marcus
 */

#ifndef TEMP_H_
#define TEMP_H_

#include "uart.h"
#include "str.h"
#include "pwm.h"

void init_temp();
void switch_mode();
void conv(float value);

#endif /* TEMP_H_ */
