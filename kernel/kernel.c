#include <common/common.h>
#include <cpu/isr.h>
#include <drivers/screen.h>
#include <kernel/kernel.h>
#include <libc/stdbool.h>
#include <libc/stdlib.h>
#include <libc/string.h>
#include <shell/command.h>

extern commands_t commands;

void user_input(char *input) {
    if (strcmp(input, "END")) {
        kprint("STOPPING THE CPU. BYE!\n");
        asm volatile("hlt");
    } else {
        handle_command(&commands, input);
        kprint("\n>>> ");
    }
}