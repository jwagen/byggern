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

static uint8_t can_message_available_var = 0;

ISR(INT2_vect){
	can_message_available_var = 1;
}

uint8_t can_message_available(){
	return can_message_available_var;
}

void can_init(){
	mcp2515_init();
	mcp2515_reset();
	
	
	//Enable interrupt on received message in both buffers
	mcp2515_write(CANINTE, (1 <<RX1IE) | (1<<RX0IE));
	
	//Receive every message, no filter
// 	mcp2515_write(RXB0CTRL, RXB_RXM1 | RXB_RXM0);
// 	
	//Set mode to normal operation
	mcp2515_write(CANCTRL,MODE_NORMAL);
	
	//Enable interrupt on falling edge of INT2, PD2, pin 19 on arduino
	EICRA |= (1<<ISC21); 
	EIMSK |= (1<<INT2);
}

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
	
}

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
/*	return message;*/
	
	
}