#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "can.h"
#include "spi.h"




int main(void)
{
	
	uart_init();
	can_init();
/*	s/pi_init();*/
	
// 	while (1)
// 	{
// 		uint8_t data = spi_transmit(0xa5);
// 		printf("Data = %a\n", data);
// 		_delay_ms(50);
// 	}
	
	

	//_delay_ms(100);

	for (uint8_t i = 0; i < 10; i++)
	{
		printf("Init done\n");
	}
	



	can_message_t m = {
		.data[0] = 0,
		.length = 0,
		.id = 1,
		
	};
	uint8_t i = 0;
	
	while(1){
		//m.data[0] = i;
		can_transmit(m);
		printf("Sent message id = %d  ", m.id);

		can_message_t r = can_recive();
		
		
		printf("Received id = %d ", r.id);
		printf("Received x pos = %d ", (int8_t)r.data[0]);
		printf("Received y pos = %d  ", (int8_t)r.data[1]);
		printf("Received length = %d\n", r.length);
		
		_delay_ms(100);

	}
	
}
