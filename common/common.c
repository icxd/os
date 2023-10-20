#include <drivers/screen.h>
#include <libc/string.h>

void panic(char *msg, char *file, int line) {
    asm volatile("cli");

    kprint("PANIC(");
    kprint(msg);
    kprint(") at ");
    kprint(file);
    kprint(":");
    kprint(itoa(line));
    kprint("\n");

    for (;;)
        ;
}

void panic_assert(char *file, int line, char *description) {
    asm volatile("cli");

    kprint("ASSERTION-FAILED(");
    kprint(description);
    kprint(") at ");
    kprint(file);
    kprint(":");
    kprint(itoa(line));
    kprint("\n");

    for (;;)
        ;
}