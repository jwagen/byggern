/*
 * slider.c
 *
 * Created: 15.09.2017 13:52:42
 *  Author: mohamama
 */ 

#include "slider.h"
#include "adc.h"
#include <stdint.h>

#define SLIDER_L_ADC_CHANNEL 4
#define SLIDER_R_ADC_CHANNEL 3


//Initializes, the adc init function is called elsewhere
void slider_init(void){
	
}

//Read left or right slider
//Returns value between 0 and 255, 0 is all the way left
uint8_t slider_read(slider_t slider){
	uint8_t result = 0;
	
	if(slider == LEFT_SLIDER){
		result = adc_read(SLIDER_L_ADC_CHANNEL);
	}
	
	else if(slider == RIGHT_SLIDER){
		result = adc_read(SLIDER_R_ADC_CHANNEL);
	}
	
	return result;
}