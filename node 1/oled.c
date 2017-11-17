/*
 * oled.c
 *
 * Created: 22.09.2017 09:16:13
 *  Author: mohamama
 */ 

#include "oled.h"
#include "fonts.h"
#include <avr/pgmspace.h>
#include <string.h>

static volatile char *oled_data_address = (char *) 0x1200;
static volatile char *oled_command_address = (char *) 0x1000;


 FILE oled_str = FDEV_SETUP_STREAM (oled_puts, NULL, _FDEV_SETUP_RW);

//Dedicate entire available sram to display buffers 
static volatile char * oled_buffer_0_address = (char *) 0x1800;
//static volatile char * oled_buffer_1_address = (char *) 0x1C00;

static volatile char * oled_buffer_current;

static uint8_t oled_inverted_state = 0;
static uint8_t oled_changed_content = 1;
 
 typedef struct{
	 uint8_t cursor_x;
	 uint8_t cursor_y;
 }oled_state_t;
 
static oled_state_t oled_state = {0};
 

//Initializes the display
void oled_init(void){
	oled_buffer_current = oled_buffer_0_address;
	
	oled_write_command(0xae); // display off
	oled_write_command(0xa1); //segment remap
	oled_write_command(0xda); //common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); //common output scan direction:com63~com0
	oled_write_command(0xa8); //multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); //contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); //set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); //Set Memory Addressing Mode to page addressing
	oled_write_command(0x02);
	oled_write_command(0xdb); //VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); //master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); //out follows RAM content
	oled_write_command(0xa6); //set normal display
	
	oled_clear(); //Clear the display
	oled_write_command(0xaf); // display on
	
	
	
	oled_clear(); //Clear the display
	
}

//Writes data to the display
void oled_write_data(uint8_t data){
	*oled_data_address = data;
	
	
}


//Writes a command to the display
void oled_write_command(uint8_t command){
	*oled_command_address = command;
}

void oled_reset(void){
	
}

void oled_home(void){
	
}

void oled_goto_line(uint8_t line){
	oled_state.cursor_y = line & 0x07;
	
	oled_write_command(0xb0 | (0x07 & oled_state.cursor_y));
}

void oled_goto_column(uint8_t column){
	oled_state.cursor_x = column & 0x8F;
	
	oled_write_command(0x0F & oled_state.cursor_x);
	oled_write_command((1<<4) | oled_state.cursor_x >> 4);
}

//Clear single line(page)
void oled_clear_line(uint8_t line){
	oled_goto_line(line);
	for(uint8_t i = 0; i < 128; i++){
		oled_write_buffer(0x00);
		//oled_write_data(0x00);
	}
}

//Clear whole display
void oled_clear(void){
	//for(uint8_t j = 0; j < 8; j++){
	//	oled_clear_line(j);
	//}
	memset((void*)oled_buffer_0_address, 0, 1024);
	//memset((void*)oled_buffer_1_address, 0, 1024);
}

void oled_pos(uint8_t column, uint8_t row){
	oled_goto_line(row);
	oled_goto_column(column);
}

void oled_inverted(uint8_t inv){
	oled_inverted_state = inv;
}


uint8_t oled_puts(char c, FILE* stream){
	if(c == '\n'){
		oled_pos(0, oled_state.cursor_y + 1); // Go to new line
	}
	
	else{
		for(uint8_t i = 0; i < 8; i++)
		{
			uint8_t data = pgm_read_byte(&font8[c - ' '][i]);
			if(oled_inverted_state){
				data = ~data;
			}
			oled_write_buffer(data);
			//oled_write_data(data);
			
		}
	}
	return 0;
}

void oled_display_bitmap(const unsigned char* bitmap){
	oled_pos(0,0);
	for(uint8_t y = 0; y<8; y++){
		for (uint8_t x = 0;x < 128; x++){
			uint8_t data = oled_reverse_bits(pgm_read_byte(bitmap + (x) + (y*128)));
			oled_write_data(data);
		}
		oled_pos(0, y);
		
	}
}

void oled_write_buffer(uint8_t data){
	uint16_t offset = oled_state.cursor_x+ ((oled_state.cursor_y)*128);
	if(data != oled_buffer_current[offset]){
		oled_changed_content = 1;	
	}
	  
	oled_buffer_current[offset] = data;
	oled_state.cursor_x++;
	
//	printf("Offset = %d\n", offset);
// 	printf("Wrote %d to %x, read back %d ", data, (uint16_t)oled_buffer_current, (uint16_t)&oled_buffer_current[offset]);
// 	printf("address = %d at x = %d, y = %d \n",oled_state.cursor_x+ (oled_state.cursor_y*128), oled_state.cursor_x, oled_state.cursor_y);
}

void oled_display_buffer(){
	if(oled_changed_content){
		oled_pos(0,0);
		for(uint8_t y = 0; y<8; y++){
			oled_pos(0, y);
			for (uint8_t x = 0;x < 128; x++){
				uint8_t data = oled_buffer_0_address[x+ ((y)*128)];
				oled_write_data(data);
			}
			
			
		}
		printf("Wrote buffer\n");
	}
	oled_changed_content = 0;
	
	//printf("start copy");
	//memcpy(oled_buffer_current, oled_buffer_1_address, 1024);
	//printf("end copy");
	
	//Change buffers
// 	if (oled_buffer_current == oled_buffer_0_address){
// 		oled_buffer_current = oled_buffer_1_address;
// 		
// 	}
// 	else{
// 		oled_buffer_current = oled_buffer_0_address;
// 	}
	//printf("Current buffer is %x \n", (uint16_t)oled_buffer_current);
	
}

//Swaps the order of bits
uint8_t oled_reverse_bits(uint8_t a){
	return ((a & 0x1)  << 7) | ((a & 0x2)  << 5) |
	((a & 0x4)  << 3) | ((a & 0x8)  << 1) |
	((a & 0x10) >> 1) | ((a & 0x20) >> 3) |
	((a & 0x40) >> 5) | ((a & 0x80)  >> 7);
}


