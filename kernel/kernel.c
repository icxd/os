#include <common/common.h>
#include <cpu/isr.h>
#include <drivers/screen.h>
#include <kernel/kernel.h>
#include <libc/stdlib.h>
#include <libc/string.h>
#include <shell/command.h>

void dummy_padding_function() {}

static void cmd_help(commands_t *commands, string *args) {
    UNUSED(args);
    kprint("AVAILABLE COMMANDS (");
    kprint(itoa(commands->commands_count));
    kprint("):\n");
    for (int i = 0; i < commands->commands_count; i++) {
        kprint(" - ");
        kprint(commands->commands[i].name.data);
        kprint("\n");
    }
}

static void cmd_clear(commands_t *commands, string *args) {
    UNUSED(commands);
    UNUSED(args);
    clear_screen();
}

static void cmd_echo(commands_t *commands, string *args) {
    UNUSED(commands);
    kprint(args->data);
    kprint("\n");
}

static commands_t commands;

void main() {
    isr_install();
    irq_install();

    asm("int $2");
    asm("int $3");

    commands = (commands_t){0};

    register_command(&commands, SV("HELP"), 0, cmd_help);
    register_command(&commands, SV("CLEAR"), 0, cmd_clear);
    register_command(&commands, SV("ECHO"), -1, cmd_echo);

    clear_screen();

    kprint("WELCOME TO PLUH OS\n\n");
    kprint(">>> ");
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("STOPPING THE CPU. BYE!\n");
        asm volatile("hlt");
    } else {
        handle_command(&commands, input);
        kprint("\n>>> ");
    }
}