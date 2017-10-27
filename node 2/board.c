/*
 * board.c
 *
 * Created: 27.10.2017 12:14:23
 *  Author: johanwaa
 */ 

#include "adc.h"

static const uint16_t beam_threshold = 50;

void board_init(){
	adc_init();
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