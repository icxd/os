#ifndef _PLUH_OS__DRIVERS__SCREEN_H_
#define _PLUH_OS__DRIVERS__SCREEN_H_

#include <stdint.h>

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLUMNS 80

#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_LIGHT_GREY 7
#define COLOR_DARK_GREY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_LIGHT_BROWN 14
#define COLOR_WHITE 15

#define FOREGROUND(c) (c & 0x0f)
#define BACKGROUND(c) (c << 4)

#define WHITE_ON_BLACK (FOREGROUND(COLOR_WHITE) | BACKGROUND(COLOR_BLACK))
#define RED_ON_WHITE (FOREGROUND(COLOR_RED) | BACKGROUND(COLOR_WHITE))

/* screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

static uint8_t terminal_color;

/* public kernel api */
void clear_screen();
void kprint_at(char *message, int column, int row);
void kprint(char *message);
void kprint_backspace();

void set_terminal_color(uint8_t color);

#endif // _PLUH_OS__DRIVERS__SCREEN_H_
