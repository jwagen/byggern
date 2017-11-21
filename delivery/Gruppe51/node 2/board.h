/*
 * board.h
 *
 * Created: 27.10.2017 12:14:46
 *  Author: johanwaa
 */ 


#ifndef BOARD_H_
#define BOARD_H_

#include <stdint.h>

void board_init();

void board_update_ball_status();
//Returns one if ball is down
uint8_t board_get_ball_status();


void board_solenoid_trigger() ;







#endif /* BOARD_H_ */