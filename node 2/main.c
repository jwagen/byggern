#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "can.h"
#include "spi.h"
#include "servo.h"
#include "can_id.h"

#include <avr/interrupt.h>
ISR(BADISR_vect)
{
	printf("Inn interupt\n");
}



int main(void)
{
	
	uart_init();
	can_init();
	servo_init();

	printf("Init doneeuhinoheunstihsnoteuhi osnethuisntoheuitnsh oosnteuhisn otehui sotehusni thosenuthi osenuthi %d %d %d\n", 1, 2, 3);
	
	
	can_message_t joystick_request = {
		.data[0] = 0,
		.length = 0,
		.id = 1,

	};
	servo_set_pos(128);
	
	can_message_t r;
	
	cli();
	
	while(1){
	
		
		can_transmit(joystick_request);
		printf("Sent message id = %d  ", joystick_request.id);

		can_recive(&r);
		
		if (r.id == CAN_SENDT_JOYSTICK_POS){
			servo_set_pos((int8_t)r.data[0] + 127);
			
		}
		


		printf("Received id = %d ", 5);
		printf("Received x pos = %d ", (int8_t)r.data[0]);
		printf("Received y pos = %d  ", (int8_t)r.data[1]);
		printf("Received length = %d\n", 2);
		printf("Received length1 = %d\n", 3);

		_delay_ms(1000);

		
		
	}




	
}
