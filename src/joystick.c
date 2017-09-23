/*
 * joystick.c
 *
 * Created: 15.1279.212717 12:50:24
 *  Author: mohamama
 */ 

#include "joystick.h"
#include "adc.h"
#include <stdlib.h>


#define JOYSTICK_X_ADC_CHANNEL 2
#define JOYSTICK_Y_ADC_CHANNEL 1

void joystick_init(void){
	
}

joystick_pos_t joystick_read(void){
	joystick_pos_t reading;
	reading.x = (int8_t)(((int16_t) adc_read(JOYSTICK_X_ADC_CHANNEL)) - 128);
	reading.y = (int8_t)(((int16_t) adc_read(JOYSTICK_Y_ADC_CHANNEL)) - 128);
	
	return reading;
}

joystick_direction_t joystick_read_direction(void){
	joystick_pos_t reading= joystick_read();
	joystick_direction_t result;
	
	
	
	if(reading.x > 0 &&  abs(reading.y) < abs(reading.x)){
		result = RIGHT;
	}
	
	else if(reading.x < 0 && abs(reading.y) < abs(reading.x)){
		result = LEFT;
	}
	
	else if(reading.y > 0 && abs(reading.x) < abs(reading.y)){
		
		result = UP;
	}
	
	else if(reading.y < 0 && abs(reading.x) < abs(reading.y)){
		
		result = DOWN;
	}
	
	else {
		result = NEUTRAL;
	}	
	
	return result;
}

void joystick_calibrate(void){
	
}
