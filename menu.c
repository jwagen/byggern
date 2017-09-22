/*
 * menu.c
 *
 * Created: 22.09.2017 17:06:54
 *  Author: mohamama
 */

#include "menu.h"
#include <stdint.h> 
#include <stdio.h>
#include "oled.h"

#include <avr/pgmspace.h>




const Menu MenuMain = {
	.header = "Main menu",
	.selected = 0,
	.items = {
		{
			.name = "Item 1"
		},
		{
			.name = "Item 2"
		},
		{
			.name = "Item 3"
		}

	}
};

uint8_t menu_display(Menu menu){
	oled_pos(12, 0);

	fprintf(&oled_str, "%s", menu.header);
	for(uint8_t i = 0; i < 7; i++){
		oled_pos(12, i+1);
		fprintf(&oled_str, "%s", menu.items[i].name);

	}
	
	oled_pos(0, menu.selected +1);
	fprintf(&oled_str, "*");
	return 0;
}

