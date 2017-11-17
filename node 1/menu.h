/*
 * menu.h
 *
 * Created: 22.09.2017 17:06:41
 *  Author: mohamama
 */ 


#ifndef MENU_H_
#define MENU_H_

#include "stdint.h"
#include <avr/pgmspace.h>

//Prototype for Menu, allows menu to contain pointer to Menu
typedef struct menu Menu;


//Struct for each menu
struct menu{
	const char header[16];			//Name of menu, used in header and item text
	uint8_t selected;			//Which item in the menu that is selected
	uint8_t number_of_items;	//Number of menu items
	Menu *items[7];				//The sub menus
	Menu *parrent;				//Parent menu
	void (*enter_function)();			//Function to run when the menu is entered.
	void (*exit_function)();			//Function to run when the menu is exited.
	
	
};



//Prototype for the menues

 Menu MenuMain;
 Menu MenuSettings;
 Menu MenuDiffeculty;
 Menu MenuNewGame;
 Menu MenuTopScore;
 Menu MenuTopScoreClear;
 Menu MenuStartGame;
 Menu MenuStopGame;
 Menu MenuControlInput;
 Menu MenuControlSlider;
 Menu MenuControlJoystick;



uint8_t menu_display(Menu *menu);
void menu_update();
void menu_goto_parrent();
void menu_control_disable();
void menu_control_enable();



#endif /* MENU_H_ */