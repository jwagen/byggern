/*
 * can.c
 *
 * Created: 29.09.2017 11:00:55
 *  Author: johanwaa
 */ 

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "can.h"
#include "mcp2515.h"
#include "mcp2515_registers.h"
#include <stdio.h>

//Stores if there is a new message available
static uint8_t can_message_available_var = 0;

//Checks the interrupt pin of the can controller and sets can_message_available_var
ISR(INT1_vect){
	can_message_available_var = 1;
	//printf("New message\n");
}

//Returns 1 if a new can message is awailable
uint8_t can_message_available(){
	return can_message_available_var;
}

//Initializing all the systems needed for CAN
void can_init(){
	mcp2515_init();
	mcp2515_reset();
	
	
	//Enable interrupt on received message in buffer 0
	mcp2515_write(CANINTE, RX0IE);

			
	//Set mode to normal operation
	mcp2515_write(CANCTRL,MODE_NORMAL);
	
	
	//Enable interrupt on falling edge of INT1, PD3
	MCUCR |= (1<<ISC11); 
	GICR |= (1<<INT1);
}

//Transmits a message over can.
//The sturct passed to the function should be passed as a pointer for better memory performance.
void can_transmit(can_message_t message){
	//Use buffer 0
	
	//Load ID
	mcp2515_write(TXB0SIDH, (0xff & (message.id >> 3))); //load high
	mcp2515_write(TXB0SIDL, 0xe0 & (message.id << 5));
	
	//Set length
	mcp2515_write(TXB0DLC, 0x0f & message.length);
	
	//Load data
	for (uint8_t i = 0; i < message.length; i++){
		mcp2515_write(TXB0D0+i, message.data[i]);
	}
	
	//Send request to send
	mcp2515_rts(1);
	
	//printf("CANINTF in transmit = %d \n", mcp2515_read(CANINTF)); 
	
}

//Recive a can message. The function is called without checking can_message_available,
//it wil return the last message if there is no new message.
void can_recive(can_message_t *message){
	//Read id
	message->id = mcp2515_read(RXB0SIDH) << 3;
	message->id |= (7 & (mcp2515_read(RXB0SIDL) >> 5)) ;

	
	//Read length
	message->length = 0x0f & mcp2515_read(RXB0DLC);
	
	//Read data
	for (uint8_t i = 0; i < message->length; i++){
		message->data[i] = mcp2515_read(RXB0D0+i);
	}
	
	//Clear interrupt flags
	mcp2515_write(CANINTF, 0x00);

	can_message_available_var = 0;	

	
	
}