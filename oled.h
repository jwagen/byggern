/*
 * oled.h
 *
 * Created: 22.09.2017 09:16:26
 *  Author: mohamama
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>
#include <stdio.h>

extern FILE oled_str;



void oled_init(void);

void oled_write_data(uint8_t data);
void oled_write_command(uint8_t command);

void oled_reset(void);
void oled_home(void);
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);

void oled_clear_line(uint8_t line);
void oled_clear(void);

void oled_pos(uint8_t column, uint8_t row);

uint8_t oled_puts(char c, FILE* stream);
void oled_print(char* string);



#endif /* OLED_H_ */