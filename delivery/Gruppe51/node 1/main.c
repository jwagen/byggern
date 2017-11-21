/*
 * GccApplication1.c
 *
 * Created: 01.09.2017 09:56:39
 *  Author: mohamama
 */ 

#define F_CPU 4915200


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "uart.h"
#include "sram.h"
#include "button.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"
#include "adc.h"
#include "menu.h"
#include "can.h"
#include "can_id.h"
#include "node2.h"
#include "mcp2515.h"
#include "mcp2515_registers.h"
#include "game.h"
#include "bitmaps.h"





int main(void)
{
	//Init systems
	sram_init();
	adc_init();
	button_init();
	oled_init();
	uart_init();
	can_init();
	joystick_init();
	game_init();
	
	//Enable interrupts
	sei();
	printf("Init done\n");
	
	//Show welcome screen
	oled_display_bitmap(bitmap_welcome);
	_delay_ms(1000);

	while(1){
		
		//Run menu system
		menu_update();
		
		//Run game
		game_run();
		
		//Show content on display
		oled_display_buffer();
		
		//Wait a bit, so can bus is not flooded
		_delay_ms(10);
		
		
		
	}
	
}
