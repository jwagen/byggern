/*
 * game.c
 *
 * Created: 10.11.2017 15:43:24
 *  Author: johanwaa
 */ 

#include "game.h"
#include "button.h"
#include "joystick.h"
#include "can.h"
#include "can_id.h"
#include "button.h"
#include "slider.h"

#include <stdio.h>


static uint8_t game_started = 0;


void game_run(){
	if(game_started){
		can_message_t joystick_message;
		
		joystick_pos_t pos = joystick_read(); 
		uint8_t button = button_read(RIGHT_BUTTON);
		
		joystick_message.length = 4;
		joystick_message.data[0] = pos.x;
		joystick_message.data[1] = slider_read(RIGHT_SLIDER);
		joystick_message.data[2] = slider_read(LEFT_SLIDER);
		joystick_message.data[3] = button;
		
		joystick_message.id = CAN_SENDT_JOYSTICK_POS;
		
		can_transmit(joystick_message);
			
	}
	
}

void game_start(){
	game_started = 1;
}

void game_stop(){
	game_started = 0;
}
