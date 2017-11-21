/*
 * bitmaps.h
 *
 * Created: 17.11.2017 16:27:03
 *  Author: johanwaa
 */ 


#ifndef BITMAPS_H_
#define BITMAPS_H_

#include <avr/pgmspace.h>

#define BITMAPS_SIZE 1024
//This file stores bitmaps for the oled display.
//Each bitmap is 1024 bytes large, til limits the number of bitmaps it is possible to put into memory.

const unsigned char bitmap_bygg[BITMAPS_SIZE];
//Created using dot2pic.com
const unsigned char bitmap_welcome[BITMAPS_SIZE];
//Created using dot2pic.com
const unsigned char bitmap_game_over[BITMAPS_SIZE];
#endif /* BITMAPS_H_ */