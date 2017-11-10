/*
 * board.c
 *
 * Created: 27.10.2017 12:14:23
 *  Author: johanwaa
 */ 

#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>

static const uint16_t beam_threshold = 50;

void board_init(){
	adc_init();
	DDRH |= (1<<PH0);
	PORTH |= (1<<PH0);

	
}

//Returns one if ball is down
uint8_t board_get_ball_status(){
	uint16_t reading = adc_read(0);
	if(reading < beam_threshold){
		return 1;
	}
	
	else {
		return 0;
	}
	
}
void board_solenoid_trigger() {
	PORTH &= ~(1<<PH0);
	_delay_ms(40);
	PORTH |= (1<<PH0);
}