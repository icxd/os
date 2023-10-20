#include <drivers/screen.h>
#include <libc/string.h>

void panic(char *msg, char *file, int line) {
    asm volatile("cli");

    set_terminal_color(FOREGROUND(COLOR_LIGHT_RED) | BACKGROUND(COLOR_BLACK));
    kprint("PANIC(");
    kprint(msg);
    kprint(") at ");
    kprint(file);
    kprint(":");
    kprint(sitoa(line));
    kprint("\n");
    set_terminal_color(WHITE_ON_BLACK);

    asm("hlt");
}

void spanic(char *msg) {
    asm volatile("cli");

    set_terminal_color(FOREGROUND(COLOR_LIGHT_RED) | BACKGROUND(COLOR_BLACK));
    kprint("PANIC(");
    kprint(msg);
    kprint(")\n");
    set_terminal_color(WHITE_ON_BLACK);

    asm("hlt");
}

void panic_assert(char *file, int line, char *description) {
    asm volatile("cli");

    set_terminal_color(FOREGROUND(COLOR_LIGHT_RED) | BACKGROUND(COLOR_BLACK));
    kprint("ASSERTION-FAILED(");
    kprint(description);
    kprint(") at ");
    kprint(file);
    kprint(":");
    kprint(sitoa(line));
    kprint("\n");
    set_terminal_color(WHITE_ON_BLACK);

    asm("hlt");
}

void debug(char *msg, char *file, int line, ...) {
    asm volatile("cli");

    set_terminal_color(FOREGROUND(COLOR_LIGHT_BROWN) | BACKGROUND(COLOR_BLACK));
    kprint("DEBUG(");
    kprint(file);
    kprint(":");
    kprint(sitoa(line));
    kprint(") ");
    kprint(msg);
    kprint("\n");
    set_terminal_color(WHITE_ON_BLACK);
}