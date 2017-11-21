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
	//Initialize the system
	uart_init();
	printf("Starting init\n");
	can_init();
	servo_init();
	board_init();
	motor_init();
	board_init();

	sei();


	printf("Init done\n");
	
	
	
	servo_set_pos(128);
	//Stores the previous state of the ball
	//Should perhaps be moved to the board file
	uint8_t previous_ball_status = 0;
	while(1){
		//Check if there is a new message
		if(can_message_available()){
			//Update moter parametrs if correct message id is recived
			can_message_t r;
			can_recive(&r);
			if (r.id = CAN_SENDT_JOYSTICK_POS){
				servo_set_pos(255 - r.data[1]);
				
				int8_t xpos = (int8_t)r.data[2] + 128;
				
				motor_enable(1);
				uint8_t button=r.data[3];
				if (button )
				{
					board_solenoid_trigger() ;
				}
				
				
				motor_set_pos(xpos);
			}
		}
	
		//Send a can message if the ball goes down, but only sends it once.
	
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
		
	



	}

	
}
