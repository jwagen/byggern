/*
 * button.h
 *
 * Created: 15.09.2017 12:32:46
 *  Author: mohamama
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>

//All available button inputs
typedef enum {
	LEFT_BUTTON = 0,
	RIGHT_BUTTON = 1,
	JOYSTICK_BUTTON = 2
}buttons_t;

//The different states of a button
typedef enum {
	LOW = 0,
	HIGH = 1,
	RISING  =2,
	FALLING = 3
} button_states_t;



void button_init(void);
uint8_t button_read(buttons_t button);
button_states_t button_read_state(buttons_t button);




#endif /* BUTTON_H_ */