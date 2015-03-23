/*
 * str.h
 *
 *  Created on: 23 Mar 2015
 *      Author: Marcus
 */

#ifndef STR_H_
#define STR_H_

#include <math.h>

int int2str(int num, int maxlen, char str[], int* len);
int float2str(float num,int decimals, int maxlen, char str[], int* len);

int round(float num);

#endif /* STR_H_ */
