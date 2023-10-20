#include <cpu/ports.h>
#include <drivers/screen.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* declaration of private functions */
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

/* public kernel api functions */
void clear_screen() {
    int screen_size = MAX_COLUMNS * MAX_ROWS;
    int i;
    char *screen = (char *)VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = terminal_color;
    }
    set_cursor_offset(get_offset(0, 0));
}

void kprint_at(char *message, int column, int row) {
    int offset;
    if (column >= 0 && row >= 0)
        offset = get_offset(column, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        column = get_offset_col(offset);
    }

    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], column, row, terminal_color);
        row = get_offset_row(offset);
        column = get_offset_col(offset);
    }
}

void kprint(char *message) { kprint_at(message, -1, -1); }

void kprint_backspace() {
    int offset = get_cursor_offset() - 2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row, terminal_color);
}

void set_terminal_color(uint8_t color) { terminal_color = color; }

/* private kernel functions */

int print_char(char c, int col, int row, char attr) {
    uint8_t *vidmem = (uint8_t *)VIDEO_ADDRESS;
    if (!attr)
        attr = WHITE_ON_BLACK;

    /* Error control: print a red 'E' if the coords aren't right */
    if (col >= MAX_COLUMNS || row >= MAX_ROWS) {
        vidmem[2 * (MAX_COLUMNS) * (MAX_ROWS)-2] = 'E';
        vidmem[2 * (MAX_COLUMNS) * (MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else
        offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    } else if (c == 0x08) { /* Backspace */
        vidmem[offset] = ' ';
        vidmem[offset + 1] = attr;
    } else {
        vidmem[offset] = c;
        vidmem[offset + 1] = attr;
        offset += 2;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLUMNS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++)
            memcpy(get_offset(0, i) + VIDEO_ADDRESS,
                   get_offset(0, i - 1) + VIDEO_ADDRESS, MAX_COLUMNS * 2);

        /* Blank last line */
        char *last_line = get_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLUMNS * 2; i++)
            last_line[i] = 0;

        offset -= 2 * MAX_COLUMNS;
    }

    set_cursor_offset(offset);
    return offset;
}

int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLUMNS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLUMNS); }
int get_offset_col(int offset) {
    return (offset - (get_offset_row(offset) * 2 * MAX_COLUMNS)) / 2;
}