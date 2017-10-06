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
#include "node2.h"




int main(void)
{
	
	sram_init();
	adc_init();
	button_init();
	oled_init();
	uart_init();
	can_init();
	joystick_init();
	
	

	_delay_ms(100);

	printf("Init done\n");
	


	can_message_t m = {
		.data[0] = 1,
		.length = 1,
		.id = 1,
			
		};
	uint8_t i = 0;
	
	while(1){

		_delay_ms(100);
		
		can_message_t r = can_recive();
		node2_send_requested_data(r);
		
		//printf("Sendt message = %d\n", m.data[0]);
		printf("Recived id = %d\n", r.id);

	}
	
}
