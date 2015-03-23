/*
 * str.c
 *
 *  Created on: 19 Mar 2015
 *      Author: Marcus
 */

#include "str.h"

int int2str(int num, int maxlen, char str[], int* len){
	int ret = -2;
	if(maxlen <= 0){
		return -1;			//Error: Overflow
	}

	if(num < 0){
		num = -num;
		str[0] = '-';
		ret = int2str(num, maxlen -1, &str[1], len);
		*len++;
	}else if(num > 9){
		int tmp_len;
		ret = int2str(num / 10, maxlen -1, str, len);
		int2str(num % 10, 1, &str[*len], &tmp_len);
		*len += tmp_len;
	}else{
		str[0] = '0' + num;
		*len = 1;
		return 0;
	}
	return ret;
}

int float2str(float num,int decimals, int maxlen, char str[], int* len){
	int i_num = num;
	int d_num = round( (num - i_num) * pow(10, decimals));

	int ret = int2str(i_num, maxlen-(decimals+1), str, len);
	if(ret){
		return ret;
	}

	str[*len] = '.';
	(*len)++;

	int dec_len;
	char dec_str[decimals];

	ret = int2str(d_num, decimals, dec_str, &dec_len);
	if(ret){
		return ret;
	}

	int i = 0;
	int j = 0;
	while(i<decimals){
		if( (dec_len + i) < decimals){
			str[*len] = '0';
			(*len)++;
		}
		else{
			str[*len] = dec_str[j];
			(*len)++;
			j++;
		}
		i++;
	}

	return 0;
}

int round(float num){
	int integer = num;

	if(num-integer >= 0.5){
		integer++;
	}

	return integer;
}
