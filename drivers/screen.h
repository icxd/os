#ifndef _PLUH_OS__DRIVERS__SCREEN_H_
#define _PLUH_OS__DRIVERS__SCREEN_H_

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLUMNS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

/* screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* public kernel api */
void clear_screen();
void kprint_at(char *message, int column, int row);
void kprint(char *message);
void kprint_backspace();

#endif // _PLUH_OS__DRIVERS__SCREEN_H_