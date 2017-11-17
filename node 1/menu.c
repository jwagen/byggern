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


uint8_t menu_control_input_disabled = 0;
uint8_t menu_changed = 1;

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
	.enter_function = NULL,
	.exit_function = NULL
};

Menu MenuSettings = {
	.header = "Settings",
	.selected = 0,
	.number_of_items = 3,
	.parrent = &MenuMain,
	.items = {
		&MenuControlInput,
		&MenuDiffeculty,
		&MenuTopScoreClear
	},
	.enter_function = NULL,
	.exit_function = NULL

};

 Menu MenuDiffeculty = {
	 .header = "Difficulty",
	 .parrent = &MenuSettings,
	 .number_of_items = 0,
	 .enter_function = NULL,
	 .exit_function = NULL
 };
 
Menu MenuControlInput = {
	.header = "Change controls",
	.parrent = &MenuSettings,
	.number_of_items = 2,
	.items = {
		&MenuControlJoystick,
		&MenuControlSlider
	},
	.enter_function = NULL,
	.exit_function = NULL
};

Menu MenuControlSlider = {
	.header = "Slider",
	.parrent = &MenuControlInput,
	.number_of_items = 0,
	.enter_function = &game_control_set_slider,
	.exit_function = NULL
};

Menu MenuControlJoystick = {
	.header = "Board joystick",
	.parrent = &MenuControlInput,
	.number_of_items = 0,
	.enter_function = &game_control_set_joystick,
	.exit_function = NULL
};
 
 Menu MenuNewGame = {
	 .header = "New game",
	 .parrent = &MenuMain,
	 .number_of_items = 2,
	 .items = {
		 &MenuStartGame,
		 &MenuStopGame,
	 },
	 .enter_function = NULL,
	 .exit_function = NULL

 };
 
Menu MenuTopScoreClear = {
	.header = "Clear top score",
	.parrent = &MenuSettings,
	.number_of_items = 0,
	.enter_function = &game_top_score_clear,
	.exit_function = NULL
};
 
Menu MenuStartGame = {
	  .header = "Start new game",
	  .parrent = &MenuMain,
	  .number_of_items = 0,
	  .enter_function = &game_start,
	  .exit_function = &game_stop
};
Menu MenuStopGame = {
	.header = "Stop the game",
	.parrent = &MenuMain,
	.number_of_items = 0,
	.enter_function = &game_stop,
	.exit_function = &game_stop
};
 Menu MenuTopScore = {
	 .header = "Top score",
	 .parrent = &MenuMain,
	 .number_of_items = 0,
	 .enter_function = &game_display_top_score,
	 .exit_function = NULL
 };
 



//Displays the a menu struct
uint8_t menu_display(Menu *menu){
	
	//Don't display a menu for menus that call functions
	//These functions are responsible for drawing to the screen them selfs
	if (menu->enter_function != NULL){
		return 0;
	}
	
	oled_pos(0, 0);

	fprintf(&oled_str, "%-16s", menu->header);
	for(uint8_t i = 0; i < 7; i++){
		oled_pos(0, i+1);
		if(i < menu->number_of_items){
			if (i == menu->selected){
				oled_inverted(1);
			}
			else{
				oled_inverted(0);
			}
			
			fprintf(&oled_str, "%-16s", menu->items[i]->header);
		}
		else{
			oled_inverted(0);
			printf("Cleared line %i", i+1);
		}
		
	}
	oled_inverted(0);
	return 0;
}

void menu_update(){

	//Do nothing if the controll inputs are disabled
	if (!menu_control_input_disabled)
	{
		void (*enter_function_temp)() = NULL;
		void (*exit_function_temp)() = NULL;

		if(joystick_read_direction() == UP){
			if(0 < currentMenu->selected ){
				currentMenu->selected--;
			}
			menu_changed = 1;
			
		}
		
		else if(joystick_read_direction() == DOWN){
			if(currentMenu->number_of_items > currentMenu->selected +1){
				currentMenu->selected++;
			}
			menu_changed = 1;
		}
		
		else if(joystick_read_direction() == RIGHT){
			if(currentMenu->items[currentMenu->selected] != NULL){
				currentMenu = currentMenu->items[currentMenu->selected];
				//Clear line if menu is updated
				oled_clear();
			}
			enter_function_temp = currentMenu->enter_function;
			menu_changed = 1;
			

		}
		
		else if(joystick_read_direction() == LEFT){
			//Run on exit menu, normaly used for cleanup functions
			exit_function_temp = currentMenu->exit_function;
			if(exit_function_temp != NULL){
				exit_function_temp();
			}
		
			if(currentMenu->parrent != NULL){
				currentMenu = currentMenu->parrent;
				//Clear line if menu is updated
				oled_clear();
			}
			menu_changed = 1;
			
		}
		
		//Run function associated with menu if it exists and button is pressed
		if(enter_function_temp != NULL){
			enter_function_temp();
		}
		if(menu_changed) {
			menu_display(currentMenu);
			menu_changed = 0;
		}
	
		
		//Wait for joystick to be in neutral
		while(joystick_read_direction() != NEUTRAL);
		_delay_ms(20);

	}

}

void menu_goto_parrent(){
	if(currentMenu->parrent != NULL){
		currentMenu = currentMenu->parrent;
		//Clear line if menu is updated
		oled_clear();
	}
}

//Make menu handler ignore button inputs
//Has to be re enabled for the menu to work again
void menu_control_disable(){
	menu_control_input_disabled = 1;
}

//Activates button inputs for menu handler
void menu_control_enable(){
	menu_control_input_disabled = 0;
}

