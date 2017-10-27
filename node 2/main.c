#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "can.h"
#include "spi.h"
#include "servo.h"
#include "can_id.h"
#include "mcp2515.h"
#include "mcp2515_registers.h"

#include <avr/interrupt.h>



int main(void)
{
	
	uart_init();
	can_init();
	servo_init();

	sei();


	printf("Init done\n");
	
	can_message_t joystick_request;
	can_message_t r = {.id = 0};


	
	
	while(1){	
		can_transmit(joystick_request);
		printf("Sent message id = %d  | ", joystick_request.id);
		
		
		
		joystick_request.id++;
		if (joystick_request.id > 2000){
			joystick_request.id = 0;
		}
		
		printf("Error message = %02x | ", mcp2515_read(EFLG));
		printf("Receive error counter = %02x | ", mcp2515_read(REC));
		printf("Transmit error counter = %02x | ", mcp2515_read(TEC));
		
		
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
