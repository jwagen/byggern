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
	
	//Enable interrupts
	sei();


	printf("Init done\n");

	while(1){

		menu_update();
		game_run();

		
	}
	
}
