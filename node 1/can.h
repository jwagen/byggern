/*
 * can.h
 *
 * Created: 29.09.2017 11:01:08
 *  Author: johanwaa
 */ 


#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>
#include "mcp2515.h"

typedef struct can_message {
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
}can_message_t;

void can_init();

void can_transmit(can_message_t);

can_message_t can_recive();





#endif /* CAN_H_ */