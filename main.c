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

#include "uart.h"
#include "sram.h"
#include "button.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"
#include "adc.h"
#include "menu.h"




int main(void)
{
	
	sram_init();
	adc_init();
	button_init();
	oled_init();
	uart_init();
	
	

	_delay_ms(100);

	printf("Init done\n");
	

	menu_display(MenuMain);

	while(1){
		
		
		char c[10];
 		fscanf(&uart_str, "%c", c);
// 		
// 
// 		fprintf(&oled_str,"%s", c);
// 		fprintf(&uart_str,"%s", c);

// 		fprintf(&oled_str,"Helasdegsdf\n asdfasdf \n \n sdfsjdlkf \n asd");
// 		
// 		printf("HEDzsdfzsdfF\n");
// 
// 
// 			
// 		_delay_ms(100);

		
	}
	
}
