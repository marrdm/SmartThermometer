/*
 * temp.c
 *
 *  Created on: 23 Mar 2015
 *      Author: Marcus
 */

#include "temp.h"

int temp_mode = 0;		// 0 = Celcius, 1 = Fahrenheit, 2 = Kelvin

void init_temp(){

}

void switch_mode(){
	 temp_mode++;
	 if(temp_mode>2){
		 temp_mode=0;
	 }
}

void conv(float value){
	static float temp;
	char temp_str[12];
	int temp_len;

	int colour = 11878 - 20.8435 * value;
	pwm_red(colour - 255);
	pwm_blue(255 - colour);
	pwm_green(255 - (colour/2));

	if(temp_mode == 0){
		temp = 247.456 - 0.4079 * value;

		float2str(temp, 1, 12, temp_str, &temp_len);
		uart_send(temp_str, temp_len);
		uart_send("°C\r\n", 5);
	}
	else if(temp_mode == 1){
		temp = 477.4 - 0.7342 * value;

		float2str(temp, 1, 12, temp_str, &temp_len);
		uart_send(temp_str, temp_len);
		uart_send("°F\r\n", 5);
	}
	else{
		temp = 520.606 - 0.4079 * value;

		float2str(temp, 1, 12, temp_str, &temp_len);
		uart_send(temp_str, temp_len);
		uart_send(" K\r\n", 4);
	}

	lcd_clear();
	SPISend(lcd, 0xA0);
	SPISend(lcd, 0xA0);
	SPISend(lcd, 0xA0);
	SPISend(lcd, 0xA0);
	SPISend(lcd, 0xA0);
	SPISend(lcd, temp_str[0]);
	SPISend(lcd, temp_str[1]);
	SPISend(lcd, temp_str[2]);
	SPISend(lcd, temp_str[3]);

	if(temp_mode == 2){
		SPISend(lcd, temp_str[4]);
		SPISend(lcd, 0xA0);										//degree symbol
		SPISend(lcd, 0x4B);
	}
	else if(temp_mode == 1) {
		if(temp_str[3] == '.') SPISend(lcd, temp_str[4]);
		SPISend(lcd, 0xDF);									//degree symbol
		SPISend(lcd, 0x46);									//F
	}
	else {
		SPISend(lcd, 0xDF);									//degree symbol
		SPISend(lcd, 0x43);									//C
	}
}
