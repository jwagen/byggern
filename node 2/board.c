/*
 * board.c
 *
 * Created: 27.10.2017 12:14:23
 *  Author: johanwaa
 */ 

#include "board.h"
#include "motor.h"
#include "adc.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t ball_down_counter = 0;
uint8_t ball_status = 0;

static const uint16_t beam_threshold = 50;

//Runs every 20ms. Uses same timer as the servo
ISR(TIMER1_OVF_vect){
	motor_update_pid();
	board_update_ball_status();
}



void board_init(){
	adc_init();
	DDRH |= (1<<PH0);
	PORTH |= (1<<PH0);

	
}

void board_update_ball_status(){
	uint16_t reading = adc_read(0);
	if(reading < beam_threshold){
		
		if (ball_down_counter >= 2){
			
			ball_status = 1;
		}
		else{
			ball_status = 0;
			ball_down_counter++;
		}
		
	}
	
	else {
		ball_down_counter = 0;
		ball_status = 0;
	}
}

//Returns one true if ball is down
uint8_t board_get_ball_status(){
	return ball_status;
	
}
void board_solenoid_trigger() {
	PORTH &= ~(1<<PH0);
	_delay_ms(40);
	PORTH |= (1<<PH0);
}