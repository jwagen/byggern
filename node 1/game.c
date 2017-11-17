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
#include "oled.h"
#include "menu.h"
#include "bitmaps.h"

#include <stdio.h>
#include <avr/eeprom.h>
#include <util/delay.h>


static uint8_t game_started = 0;
uint8_t game_life_counter = 0;
uint8_t game_points = 0;
//One indicates game over
uint8_t game_status = 0;

//Top score variables
uint8_t game_top_scores[7] = {0};
uint8_t EEMEM game_top_scores_rom[7];

//Controll mode
game_control_mode_t game_control_mode = JOYSTICK;

void game_init(){
	//Read in top score stored in eeprom
	eeprom_read_block((void*)game_top_scores, (const void*)game_top_scores_rom, 7);
}


//Main function that runs the game
void game_run(){
	if(game_started && !game_status){
		
		//Static so old value is sent if input read is disabled
		static uint8_t servo = 0;
		static uint8_t motor = 0;
		static uint8_t solinoid = 0;
		
		//Control the game with the sliders
		if (game_control_mode == SLIDER){
			if(button_read_state(RIGHT_BUTTON) == RISING){
				game_points++;
				solinoid = 1;
			}
			else {
				solinoid = 0;
			}
			
			servo = slider_read(RIGHT_SLIDER);
			motor = slider_read(LEFT_SLIDER);

		}
		
		//Control the game with the joystick
		else if (game_control_mode == JOYSTICK){
			//Disable menu control with the joystick while button is not pressed
			if(button_read_state(RIGHT_BUTTON) == HIGH){
				menu_control_enable();
			}
			
			else{
				menu_control_disable();
				
				//Only trigger solinoid on edge of button press
				if(button_read_state(JOYSTICK_BUTTON) == RISING){
					game_points++;
					solinoid = 1;
				}
				else {
					solinoid = 0;
				}
				
				//Read data from joystick and convert it to unsigned
				joystick_pos_t p = joystick_read();
				servo = (uint8_t)(128 + p.y);
				motor = (uint8_t)(128 + p.x);
				
			}
		}
		
		
		//Send control data over can
		can_message_t control_inputs_message;
		control_inputs_message.length = 4;
		control_inputs_message.data[1] = servo;
		control_inputs_message.data[2] = motor;
		control_inputs_message.data[3] = solinoid;
		control_inputs_message.id = CAN_SENDT_JOYSTICK_POS;
		can_transmit(control_inputs_message);
			
	
		
	
		//Check for new messages on can bus
		if(can_message_available()){
			can_message_t r;
			can_recive(&r);
		
		
			//Ball is down
			if(r.id == CAN_SENDT_BALL_DOWN){
				game_life_counter--;
				if (game_life_counter == 0){
					game_status = 1;
					menu_control_enable();
					game_new_score(game_points);
					printf("Game stopped\n");
					oled_display_bitmap(bitmap_game_over);
					_delay_ms(1000);
				}
			}
		}
		
		game_update_display();
	}	
}

//Start the game
void game_start(){
	printf("Game started\n");
	game_started = 1;
	game_life_counter = 3;
	game_points = 0;
	game_status = 0;
}

//End the game
void game_stop(){
	game_started = 0;
}

//Screen showed while the game is running, and when game over occurs
void game_update_display(){
	if (game_status){
		oled_clear();
		oled_pos(0,0);
		fprintf(&oled_str, "Game over!      ");
		oled_pos(0, 1);
		fprintf(&oled_str, "You got %d points", game_points);
		oled_pos(0,2);
		fprintf(&oled_str, "            ");
		oled_pos(0, 4);
		fprintf(&oled_str, "Right: New game");
		oled_pos(0, 5);
		fprintf(&oled_str, "Left: exit");
	}
	else{
		oled_clear();
		oled_pos(0,0);
		fprintf(&oled_str, "Lives left : %3d", game_life_counter);
		oled_pos(0, 1);
		fprintf(&oled_str, "Points     : %3d", game_points);
		oled_pos(0, 2);
		fprintf(&oled_str, "Left: exit");
	}
}

void game_over(){
	
}

//Show the top score list
void game_display_top_score(){
	oled_pos(0,0);
	fprintf(&oled_str, "   Top score");
	for(uint8_t i = 0; i < 7; i++){
		oled_pos(0, i+1);
		
		fprintf(&oled_str, "%d.   %3d", i+1,game_top_scores[i]);
	
	}
}

//Checks the score and adds it to the top score if it is high enough
void game_new_score(uint8_t score){
	
	//Check if score is larger than smallest
	if(score > game_top_scores[7-1]){
		game_top_scores[7-1] = score;
	}
	
	
	//Sort list by insertion sort
	//One iteration through the list is enough as only one new item is added to a sorted list at a time
	for (uint8_t i = 7-1; i > 0; i--){
		//Switch places if score is larger
		if(game_top_scores[i-1] < game_top_scores[i]){
			uint8_t temp = game_top_scores[i-1];
			game_top_scores[i-1] = game_top_scores[i];
			game_top_scores[i] = temp;
		}
	}
	
	//update eeprom
	eeprom_update_block((const void*)game_top_scores, (void*)game_top_scores_rom, 7);
	
}

//Clear the top scores, both in ram and eeprom
void game_top_score_clear(){
	for(uint8_t i = 0; i < 7; i++){
		game_top_scores[i] = 0;
	}
	eeprom_update_block((const void*)game_top_scores, (void*)game_top_scores_rom, 7);
	
	oled_clear();
	oled_pos(0,0);
	fprintf(&oled_str, "Top score cleared");
}

//Set the input to the sliders
void game_control_set_slider(){
	game_control_mode = SLIDER;
	
	oled_clear();
	oled_pos(0,0);
	fprintf(&oled_str, "Input set \n to slider");
}

//Set the inputs to joystick
void game_control_set_joystick(){
	game_control_mode = JOYSTICK;
	
	oled_clear();
	oled_pos(0,0);
	fprintf(&oled_str, "Input set \n to joystick");
}
