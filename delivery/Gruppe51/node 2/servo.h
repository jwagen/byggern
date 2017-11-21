/*
 * servo.h
 *
 * Created: 13.10.2017 10:54:49
 *  Author: johanwaa
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

void servo_init();

//Takes a input between 0 and 2000
//The use of 2000 maximizes the available resolusion
void servo_set_pos_highres(uint16_t);

//Set output with an 8 bit variable
void servo_set_pos(uint8_t);



#endif /* SERVO_H_ */