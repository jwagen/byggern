/*
 * servo.c
 *
 * Created: 13.10.2017 10:55:01
 *  Author: johanwaa
 */ 

#include <avr/io.h>
#include <stdint.h>

#include "servo.h"

//The period of the output should be 20 ms or 50Hz
//By equation in 17.9.3 the prescaler needs to be 64.
//TOP = (FCPU / (8 * 50)) -1 = 39999

#define SERVO_FREQUENCY 50
#define SERVO_TIMER_PRESCALER 8
#define SERVO_TIMER_TOP (uint16_t)(F_CPU / (SERVO_TIMER_PRESCALER * SERVO_FREQUENCY) - 1)

//Output signal parameters in ms
#define SERVO_PERIOD (uint16_t)((1000 / SERVO_FREQUENCY))
#define SERVO_MIN_PULSE 0.9
#define SERVO_MAX_PULSE 2.1
#define SERVO_TIMER_VAL_PER_MS (uint16_t)((SERVO_TIMER_TOP + 1) / SERVO_PERIOD)

#define SERVO_TIMER_MAX (uint16_t)(SERVO_TIMER_VAL_PER_MS * SERVO_MAX_PULSE -1)
#define SERVO_TIMER_MIN (uint16_t)(SERVO_TIMER_VAL_PER_MS * SERVO_MIN_PULSE -1)

#define SERVO_8BIT_TO_TIMER (uint16_t)((SERVO_TIMER_MAX - SERVO_TIMER_MIN)/255)



void servo_init(){
	//Use timer 1 and output OC1A PB5, pin 11 on arduino, for the pwm signal
	//Set pin as output
	DDRB |= (1<<PB5);
	
	//Enable output on OC1A, noninverted mode. Output is set at bottom, and cleared on timer reset
	TCCR1A |= (1<<COM1A1) ;	
	
	//Fast pwm mode
	//Set it to mode 14, table 17-2, counts to ICRn then resets to 0
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12);
	
	//Set counter frequency to 50Hz
	//Set top counter value
	ICR1 = SERVO_TIMER_TOP;
	//Set prescaler to 8 and start the timer
	TCCR1B |= (1<<CS11);

}


void servo_set_pos(uint8_t pos){
	uint16_t val = pos * SERVO_8BIT_TO_TIMER + SERVO_TIMER_MIN;
	
	if(val < SERVO_TIMER_MIN){
		val = SERVO_TIMER_MIN;
	}
	
	if(val > SERVO_TIMER_MAX){
		val = SERVO_TIMER_MAX;
	}
	
	OCR1A = val;
}
