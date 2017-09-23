/*
 *
 * GccApplication1.c
 *
 * Created: 01.09.2017 09:56:39
 *  Author: mohamama
 */ 

#define F_CPU 4915200


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "sram.h"
#include "button.h"
#include "joystick.h"
#include "slider.h"



int main()
{
	sram_init();
	adc_init();
	button_init();
	volatile char *ext_ADC = (char *) 0x1400; // Start address for the ADC
	uint16_t ADC_address_space = 0x400;
	
	while(1){
		uint8_t reading1 = adc_read(1);
		uint8_t reading2 = adc_read(2);
		uint8_t reading3 = adc_read(3);
		uint8_t reading4 = adc_read(4);
		uint8_t bL = button_read(LEFT_BUTTON);
		uint8_t bR = button_read(RIGHT_BUTTON);
		//printf("Channal 1 = %d | Channel 2 = %d | Channal 3 = %d | Channel 4 =%d | left button %d | right button %d\n", reading1, reading2, reading3, reading4, bL, bR);
		joystick_pos_t r = joystick_read();
		printf("x = %d | y = %d \n", r.x, r.y);
		joystick_direction_t reading = joystick_read_direction();
		switch (reading) {
			case UP:
				printf("UP\n");
				break;
			case DOWN:
				printf("DOWN\n");
				break;
			case RIGHT:
				printf("RIGHT\n");
				break;
			case LEFT:
				printf("LEFT\n");
				break;
			case NEUTRAL:
				printf("NEUTRAL\n");
				break;
			default:
				printf("Error");
			
		}
		
		uint8_t ls = slider_read(LEFT_SLIDER);
		uint8_t rs = slider_read(RIGHT_SLIDER);
		
		printf("Left slider: %d  Right slider %d \n", ls, rs);
		_delay_ms(50);
		
	}
	
}
