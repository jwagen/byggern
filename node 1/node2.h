/*
 * node2.h
 *
 * Created: 06.10.2017 12:10:37
 *  Author: johanwaa
 */ 


#ifndef NODE2_H_
#define NODE2_H_

#include "can.h"

//Sends data requested by node 2 

void node2_init();
void node2_send_requested_data(can_message_t);




#endif /* NODE2_H_ */