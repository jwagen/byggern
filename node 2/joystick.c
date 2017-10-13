/*
 * joystick.c
 *
 * Created: 15.1279.212717 12:50:24
 *  Author: mohamama
 */ 

#include "can.h"
#include "can_id.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>


#define JOYSTICK_X_ADC_CHANNEL 2
#define JOYSTICK_Y_ADC_CHANNEL 1
#define NEUTRAL_RANGE 4

static joystick_pos_t offset = {0, 0};


void joystick_init(void){

	
}

joystick_pos_t joystick_read(void){
	joystick_pos_t reading;
	reading.x = (int8_t)(((int16_t) adc_read(JOYSTICK_X_ADC_CHANNEL)) - 128) + offset.x;
	reading.y = (int8_t)(((int16_t) adc_read(JOYSTICK_Y_ADC_CHANNEL)) - 128) + offset.y;
	
	//Request posision of joystick over can
	can_transmit({0, 0, }
	
	
	return reading;
}

joystick_direction_t joystick_read_direction(void){
	joystick_pos_t reading= joystick_read();
	joystick_direction_t result;
	
	
	
	if(reading.x > NEUTRAL_RANGE &&  abs(reading.y) < abs(reading.x)){
		result = RIGHT;
	}
	
	else if(reading.x < -NEUTRAL_RANGE && abs(reading.y) < abs(reading.x)){
		result = LEFT;
	}
	
	else if(reading.y > NEUTRAL_RANGE && abs(reading.x) < abs(reading.y)){
		
		result = UP;
	}
	
	else if(reading.y < -NEUTRAL_RANGE && abs(reading.x) < abs(reading.y)){
		
		result = DOWN;
	}
	
	else {
		result = NEUTRAL;
	}	
	
	return result;
}

void joystick_calibrate(void){
	//Start calibration
	printf("Starting calibration");
	joystick_pos_t max = {0, 0}, min = {0, 0};
	//Look for largest value in x and y	
	//Stop when button is pressed
	while(button_read_state(LEFT_BUTTON) != RISING){
		joystick_pos_t reading = joystick_read();
		
		if(reading.x > max.x){
			max.x = reading.x;
		}
		
		if(reading.x < min.x){
			min.x = reading.x;
		}
		
		if(reading.y > max.y){
			max.y = reading.y;
		}
		
		if(reading.y < min.y){
			min.y = reading.y;
		}		
	}
	
	while(button_read_state(LEFT_BUTTON) != RISING){
		
	}
	
	//calculate offsets
	offset.x = (max.x - min.x)/2 - 127;
	offset.y = (max.y - min.y)/2 - 127;
	
	printf("Calibration complete with offset x: %d, y:%d\n", offset.x, offset.y);
	printf("max x:%d, y:%d, min x:%d, y:%d", max.x, max.y, min.x, min.y);

}