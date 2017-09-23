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

#include <avr/pgmspace.h>




Menu MenuMain = {
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
	oled_pos(0, menu.selected);
	fprintf(&oled_str, " ");
	oled_pos(0, menu.selected +1);
	fprintf(&oled_str, "*");
		oled_pos(0, menu.selected +2);
		fprintf(&oled_str, " ");
	return 0;
}

uint8_t menu_handle_input(Menu *menu){
	while(!button_read(JOYSTICK_BUTTON)){
		if(joystick_read_direction() == UP){
			menu->selected--;
		}
		
		else if(joystick_read_direction() == DOWN){
			menu->selected++;
		}
		
		menu_display(*menu);
		
		_delay_ms(50);
	}
	
	return menu->selected;

}
