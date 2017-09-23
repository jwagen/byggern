/*
 * joystick.h
 *
 * Created: 15.09.2017 12:50:10
 *  Author: mohamama
 */ 

#include <stdint.h>

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

typedef struct  {
	int8_t x;
	int8_t y;
} joystick_pos_t;

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL	
} joystick_direction_t;

void joystick_init(void);
joystick_pos_t joystick_read(void);
joystick_direction_t joystick_read_direction(void);
void joystick_calibrate(void);




#endif /* JOYSTICK_H_ */