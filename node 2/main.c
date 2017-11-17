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
#include "motor.h"


#include <avr/interrupt.h>



int main(void)
{
	
	uart_init();
	printf("Starting init\n");
	can_init();
	servo_init();
	board_init();
	motor_init();
	board_init();

	sei();


	printf("Init done\n");
	
	can_message_t r;

	servo_set_pos(128);
	
	uint8_t previous_ball_status = 0;
	while(1){
		
	if(can_message_available()){
		//printf("CAN message available \n");
		can_recive(&r);
		//printf("Received id = %d | ", r.id);
		//printf("Joystick pos = %d \n", (int8_t)r.data[0]);
		servo_set_pos(255 - r.data[1]);
		
		//int8_t xpos = (int8_t)r.data[0];
		int8_t xpos = (int8_t)r.data[2] + 128;
		
		//printf("xpos = %d\n", xpos);
		motor_enable(1);
		uint8_t button=r.data[3];
		if (button )
		{
			board_solenoid_trigger() ;
		}
		
		
		motor_set_pos(xpos);
	}
	
	//Send a can message if the ball goes down, but only sends it once.
	//printf("Ball status = %d \n", board_get_ball_status());
	//printf("Previous ball status = %d \n", board_get_ball_status());
	if (board_get_ball_status() != 0){
		
		
		if(previous_ball_status == 0){
			can_message_t ball_status = {
				.id = CAN_SENDT_BALL_DOWN,
				.length = 0
			};
			
			can_transmit(ball_status);
			previous_ball_status = 1;
		}
		
	}
	
	else {
		previous_ball_status = 0;
	}
	
	
		
	
			

		
		
		
		

			
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
// 
//  		printf("Error message = %02x | ", mcp2515_read(EFLG));
//  		printf("Receive error counter = %02x | ", mcp2515_read(REC));
//  		printf("Transmit error counter = %02x | ", mcp2515_read(TEC));
// 		printf("Can interrupt flags = %02x | ", mcp2515_read(CANINTF));
// 		printf("Can status = %02x | ", mcp2515_read(CANSTAT));
// 		printf("CAN interupt enable = %02x | ", mcp2515_read(CANINTE));
// 
// 
// // // 		if(can_message_available()){
// 		if(1){
// 			can_recive(&r);
// 			printf("Received id = %d | ", r.id);
// 			printf("Joystick pos = %d \n", (int8_t)r.data[0]);
// 			servo_set_pos((int8_t)r.data[0] + 128);
// 			
// 		}
// 		
// 		else {
// 			printf("No new message\n");
// 		}
// 		
// 		
// 		
// 		_delay_ms(100);
// 		
// 		uint8_t status = board_get_ball_status();
// 		
// 		if (status){
// 			printf("Game over \n");
// 		}
// 		
// 		else {
// 			printf("Ball in play\n");
// 		}
		
		//printf("ACD value = %d \n", adc_read(0));
		//_delay_ms(100);


	}

	
}
