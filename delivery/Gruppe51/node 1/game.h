/*
 * game.h
 *
 * Created: 10.11.2017 15:42:55
 *  Author: johanwaa
 */ 


#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>

uint8_t game_life_counter;

typedef enum {
	SLIDER,
	JOYSTICK
} game_control_mode_t;

void game_init();

void game_run();

void game_start();

void game_stop();

void game_update_display();

void game_over();

void game_display_top_score();
void game_new_score(uint8_t);

void game_top_score_clear();


void game_control_set_slider();

void game_control_set_joystick();





#endif /* GAME_H_ */