/*
 * menu.h
 *
 * Created: 22.09.2017 17:06:41
 *  Author: mohamama
 */ 


#ifndef MENU_H_
#define MENU_H_

#include "stdint.h" 

typedef struct menu_item{
	char name[16];
} Menu_item;


typedef struct menu{
	char header[16];
	uint8_t selected;
	Menu_item items[7];
	
} Menu;



 Menu MenuMain;


uint8_t menu_display(Menu menu);
uint8_t menu_handle_input(Menu *menu);



#endif /* MENU_H_ */