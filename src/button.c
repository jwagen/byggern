/*
 * button.c
 *
 * Created: 15.09.2017 12:32:34
 *  Author: mohamama
 */ 

#include <stdint.h>
#include <avr/io.h>

#include "button.h"

#define BUTTON_NUMBER 3

void button_init(void){
	DDRD &= ~((1<<PD1) | (1<<PD0));	//Set touch buttons as input
	
	DDRE &= ~((1<<PE0));			//Set joystick button as input
	PORTE |= (1<<PE0);				//Enable pullup
	
}

uint8_t button_read(buttons_t button){
	uint8_t reading = 0;
	if(button == LEFT_BUTTON ){
		reading = !!(PIND & (1<<PIND0));
	}
	
	else if (button == RIGHT_BUTTON){
		reading = !!(PIND & (1<<PIND1));
		
	}
	
	else if (button == JOYSTICK_BUTTON){
		reading = !(PINE & (1<<PINE0));
		
	}
	
	return reading;
}

button_states_t button_read_state(buttons_t button){
	static button_states_t current_state[BUTTON_NUMBER];
	uint8_t reading = button_read(button);
	
	if(reading && current_state[button] == LOW){
		current_state[button] = RISING;
	}
	
	else if(reading && current_state[button] == HIGH){
		current_state[button] = HIGH;
	}
	
	else if(!reading && current_state[button] == HIGH){
		current_state[button] = FALLING;
	}
	
	else if(!reading && current_state[button] == LOW){
		current_state[button] = LOW;
	}
	
	
	return current_state[button];
}