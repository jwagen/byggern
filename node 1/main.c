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
#include <avr/interrupt.h>

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
#include "mcp2515.h"
#include "mcp2515_registers.h"




int main(void)
{
	
	sram_init();
	adc_init();
	button_init();
	oled_init();
	uart_init();
	can_init();
	joystick_init();
	
	//Enable interrupts
	sei();


	printf("Init done\n");
	
	can_message_t joystick_request;
	can_message_t r;


	
	
	while(1){
// 
// 		printf("Can available = %d ", can_message_available());
// 		printf("INT2 status = %d | ", !!(PIND & (1<<PD3)));
// 		
// 		can_transmit(joystick_request);
// 		printf("Sent message id = %d  | ", joystick_request.id);
// 		
// 		
// 		joystick_request.id++;
// 		if (joystick_request.id > 2000){
// 			joystick_request.id = 0;
// 		}
		
		printf("Error message = %02x | ", mcp2515_read(EFLG));
		printf("Receive error counter = %02x | ", mcp2515_read(REC));
		printf("Transmit error counter = %02x | ", mcp2515_read(TEC));
		
		
		can_recive(&r);
		printf("Received id = %d \n ", r.id);
		if(can_message_available()){
			can_recive(&r);
			printf("Received id = %d \n ", r.id);
			
		}
		
		else {
			printf("No new message\n");
		}
		
		
		
		_delay_ms(200);
		
	}
	
}
