void __padding__() {}

#include <common/common.h>
#include <cpu/isr.h>
#include <drivers/screen.h>
#include <kernel/kernel.h>
#include <kernel/syscalls.h>
#include <libc/stdbool.h>
#include <libc/stdlib.h>
#include <libc/string.h>
#include <shell/command.h>
#include <shell/commands.h>

commands_t commands;

void kmain() {
    register_interrupt_handler(0x80, syscall_handler);

    isr_install();
    irq_install();

    asm("int $2");
    asm("int $3");

    commands = (commands_t){0};

    register_command(&commands, SV("HELP"), 0, cmd_help);
    register_command(&commands, SV("CLEAR"), 0, cmd_clear);
    register_command(&commands, SV("ECHO"), -1, cmd_echo);
    register_command(&commands, SV("LS"), 0, cmd_ls);

    set_terminal_color(WHITE_ON_BLACK);

    clear_screen();

    // sys$write(1, "Hello, kernel World!\n", 21);

    // asm("hlt");

    kprint("\n");
    set_terminal_color(FOREGROUND(COLOR_LIGHT_RED));
    kprint("   _____ __    _____ _____ \n");
    set_terminal_color(FOREGROUND(COLOR_LIGHT_BROWN));
    kprint("  |  _  |  |  |  |  |  |  |\n");
    set_terminal_color(FOREGROUND(COLOR_LIGHT_GREEN));
    kprint("  |   __|  |__|  |  |     |\n");
    set_terminal_color(FOREGROUND(COLOR_LIGHT_CYAN));
    kprint("  |__|  |_____|_____|__|__|\n");
    set_terminal_color(FOREGROUND(COLOR_LIGHT_BLUE));
    kprint("                           \n");
    kprint("\n");
    kprint("WELCOME TO PLUH OS\n\n");
    set_terminal_color(WHITE_ON_BLACK);
    kprint(">>> ");
}