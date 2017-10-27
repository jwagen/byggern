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
#include "adc.h"
#include "board.h"

#include <avr/interrupt.h>



int main(void)
{
	
	uart_init();
	can_init();
	servo_init();
	board_init();

	sei();


	printf("Init done\n");
	
	can_message_t joystick_request;
	can_message_t r = {.id = 0};


	servo_set_pos(128);
	
	uint8_t s = 1;
	while(1){
		
// 		for (s = 0; s < 255; s++){
// 			servo_set_pos(s);
// 			_delay_ms(40);
// 		}
// 		
// 		for (s = 255; s > 0; s--){
// 			servo_set_pos(s);
// 			_delay_ms(40);
// 		}
			
// 		can_transmit(joystick_request);
// 		printf("Sent message id = %d  | ", joystick_request.id);
// 		
// 		
// 		
// 		joystick_request.id++;
// 		if (joystick_request.id > 2000){
// 			joystick_request.id = 0;
// 		}
// 		
//  		printf("Error message = %02x | ", mcp2515_read(EFLG));
//  		printf("Receive error counter = %02x | ", mcp2515_read(REC));
//  		printf("Transmit error counter = %02x | ", mcp2515_read(TEC));
// // 		
// // 		
// 
// 		printf("Can available = %d | ", can_message_available());
// 		printf("INT2 status = %d | ", !!(PIND & (1<<PD2)));
// 		//Interupt does not work, Can transceiver does not toggle int pin

 		printf("Error message = %02x | ", mcp2515_read(EFLG));
 		printf("Receive error counter = %02x | ", mcp2515_read(REC));
 		printf("Transmit error counter = %02x | ", mcp2515_read(TEC));
		printf("Can interrupt flags = %02x | ", mcp2515_read(CANINTF));
		printf("Can status = %02x | ", mcp2515_read(CANSTAT));
		printf("CAN interupt enable = %02x | ", mcp2515_read(CANINTE));


// // 		if(can_message_available()){
		if(1){
			can_recive(&r);
			printf("Received id = %d | ", r.id);
			printf("Joystick pos = %d \n", (int8_t)r.data[0]);
			servo_set_pos((int8_t)r.data[0] + 128);
			
		}
		
		else {
			printf("No new message\n");
		}
		
		
		
		_delay_ms(100);
		
		uint8_t status = board_get_ball_status();
		
		if (status){
			printf("Game over \n");
		}
		
		else {
			printf("Ball in play\n");
		}
		
		//printf("ACD value = %d \n", adc_read(0));
		//_delay_ms(100);


	}

	
}
