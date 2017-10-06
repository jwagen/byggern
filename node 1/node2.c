/*
 * node2.c
 *
 * Created: 06.10.2017 12:10:23
 *  Author: johanwaa
 */ 


#include "can.h"
#include "joystick.h"
#include "uart.h"

//ID of different messages
// typedef enum {
// 	NODE2_JOYSTICK = 1
// } node2_message_id;#define REQUEST_JOYSTICK_POS 1
#define SENDT_JOYSTICK_POS 2



void node2_init(){
	
}

//Sends data requested by node 2
void node2_send_requested_data(can_message_t message){
	printf("Received id = %d ", message.id);
	//printf("Received data = %d ", message.data[0]);
	//printf("Received data = %d\n", message.data[1]);
	
	can_message_t send_message;
	if (message.id == REQUEST_JOYSTICK_POS){
		joystick_pos_t  pos = joystick_read();
		printf("Joystick pos : x = %d, y = %d\n", pos.x, pos.y);
		send_message.data[0] = pos.x;
		send_message.data[1] = pos.y;
		
		send_message.length = 2;
		send_message.id = SENDT_JOYSTICK_POS;
		
		printf("Sent message id = %d  ", send_message.id);
		printf("Sent message data = %d  ", send_message.data[0]);
		printf("Sent message id = %d  ", send_message.data[1]);
		printf("Sent message length = %d  \n", send_message.length);
		
		
		can_transmit(send_message);
		
	}
}