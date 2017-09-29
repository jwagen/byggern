/*
 * can.c
 *
 * Created: 29.09.2017 11:00:55
 *  Author: johanwaa
 */ 

#include <stdint.h>

#include "can.h"
#include "mcp2515.h"
#include "mcp2515_registers.h"


void can_init(){
	mcp2515_init();
	mcp2515_write(CANCTRL,MODE_LOOPBACK);
	
	//Enable interrupt on received message in both buffers
	mcp2515_write(CANINTE, (1 <<RX1IE) | (1<<RX0IE));
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

can_message_t can_recive(){
	can_message_t message;
	//Read id
	message.id = mcp2515_read(RXB0SIDH) << 3;
	message.id |= (7 & (mcp2515_read(RXB0SIDL) >> 5)) ;
	
	//Read length
	message.length = 0x0f & mcp2515_read(RXB0DLC);
	
	//Read data
	for (uint8_t i = 0; i < message.length; i++){
		message.data[i] = mcp2515_read(RXB0D0+i);
	}
	
	//Clear interrupt flags
	mcp2515_write(CANINTF, 0x00);
	
	return message;
	
	
}