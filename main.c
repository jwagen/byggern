/*
 * GccApplication1.c
 *
 * Created: 01.09.2017 09:56:39
 *  Author: mohamama
 */ 

#define F_CPU 4915200


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "sram.h"
#include "button.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"
#include "adc.h"
#include "menu.h"
#include "can.h"




int main(void)
{
	
	sram_init();
	adc_init();
	button_init();
	oled_init();
	uart_init();
	can_init();
	
	

	_delay_ms(100);

	printf("Init done\n");
	


	can_message_t m = {
		.data[0] = 1,
		.length = 1,
		.id = 1,
			
		};
	uint8_t i = 0;
	
	while(1){
		m.data[0] = i;
		can_transmit(m);
		_delay_ms(100);
		
		can_message_t r = can_recive();
		printf("Sendt message = %d\n", m.data[0]);
		printf("Recivede data = %d\n", r.data[0]);
		//printf("Test");
		i++;
	}
	
}
