/*
 * menu.c
 *
 * Created: 22.09.2017 17:06:54
 *  Author: mohamama
 */

#include "menu.h"
#include <stdint.h> 
#include <stdio.h>
#include <util/delay.h>
#include "oled.h"
#include "button.h"
#include "joystick.h"
#include "game.h"

#include <avr/pgmspace.h>


static Menu *currentMenu = &MenuMain;

void test(void){
	printf("Test\n");
}

Menu MenuMain = {
	.header = "Main menu",
	.selected = 0,
	.number_of_items = 3,
	.items = {
		&MenuNewGame,
		&MenuTopScore,
		&MenuSettings
	},
	.parrent = NULL,
	.function = NULL
};

Menu MenuSettings = {
	.header = "Settings",
	.selected = 0,
	.number_of_items = 1,
	.parrent = &MenuMain,
	.items = {
		&MenuDiffeculty
	},
	.function = NULL

};

 Menu MenuDiffeculty = {
	 .header = "Difficulty",
	 .parrent = &MenuSettings,
	 .number_of_items = 0,
	 .function = NULL
 };
 Menu MenuNewGame = {
	 .header = "New game",
	 .parrent = &MenuMain,
	 .number_of_items = 2,
	 .items = {
		 &MenuStartGame,
		 &MenuStopGame,
	 },
	 .function = NULL

 };
 
Menu MenuStartGame = {
	  .header = "Start new game",
	  .parrent = &MenuMain,
	  .number_of_items = 0,
	  .function = &game_start
};
Menu MenuStopGame = {
	.header = "Stop the game",
	.parrent = &MenuMain,
	.number_of_items = 0,
	.function = &game_stop
};
 Menu MenuTopScore = {
	 .header = "Top score",
	 .parrent = &MenuMain,
	 .number_of_items = 0,
	 .function = NULL
 };


//Displays the a menu struct
uint8_t menu_display(Menu *menu){
	oled_pos(12, 0);

	fprintf(&oled_str, "%-15s", menu->header);
	for(uint8_t i = 0; i < 7; i++){
		oled_pos(12, i+1);
		if(i < menu->number_of_items){
			fprintf(&oled_str, "%-15s", menu->items[i]->header);
		}
		else{
			fprintf(&oled_str,"          ");
			//oled_clear_line(i);
		}
		
		oled_pos(0, i);
		
		if (menu->number_of_items > 0 && menu->selected +1 == i){
			oled_pos(0, menu->selected +1);
			fprintf(&oled_str, "*");
		}
		else{
			fprintf(&oled_str, " ");
		}
	}

	return 0;
}

void menu_update(){

	
	
	void (*function_temp)() = NULL;

	if(joystick_read_direction() == UP){
		if(0 < currentMenu->selected ){
			currentMenu->selected--;
		}
			
	}
		
	else if(joystick_read_direction() == DOWN){
		if(currentMenu->number_of_items > currentMenu->selected +1){
			currentMenu->selected++;
		}
	}
		
	else if(joystick_read_direction() == RIGHT){
		if(currentMenu->items[currentMenu->selected] != NULL){
			currentMenu = currentMenu->items[currentMenu->selected];
			//Clear line if menu is updated
			oled_clear();
		}
		function_temp = currentMenu->function;
			

	}
		
	else if(joystick_read_direction() == LEFT){
		if(currentMenu->parrent != NULL){
			currentMenu = currentMenu->parrent;
			//Clear line if menu is updated
			oled_clear();
		}
			
	}
		
	//Run function associated with menu if it exists and button is pressed
	if(function_temp != NULL){
		function_temp();
	}
	else {
		menu_display(currentMenu);
	}
		
	//Wait for joystick to be in neutral
	while(joystick_read_direction() != NEUTRAL);
	_delay_ms(20);

	
	
	


}

