/*
 * button.c
 *
 * Created: 15.09.2017 12:32:34
 *  Author: mohamama
 */ 

#include <stdint.h>
#include <avr/io.h>

#include "button.h"

void button_init(void){
	//Set buttons as input
	DDRD &= ~((1<<PD1) | (1<<PD0));
}

uint8_t button_read(buttons_t button){
	uint8_t reading = 0;
	if(button == LEFT_BUTTON ){
		reading = !!(PIND & (1<<PIND0));
	}
	
	else if (button == RIGHT_BUTTON){
		reading = !!(PIND & (1<<PIND1));
		
	}
	
	return reading;
}