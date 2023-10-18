void __padding__() {}

#include <common/common.h>
#include <cpu/isr.h>
#include <drivers/fs.h>
#include <drivers/screen.h>
#include <kernel/kernel.h>
#include <libc/stdbool.h>
#include <libc/stdlib.h>
#include <libc/string.h>
#include <shell/command.h>

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

static void cmd_ls(commands_t *commands, string *args) {
    UNUSED(commands);
    UNUSED(args);
    directory_t *node = fs_root;
    for (int i = 0; i < node->directories_count; i++) {
        kprint(node->directories[i]->name);
        if (i != node->directories_count - 1) {
            kprint(", ");
        }
    }
    for (int i = 0; i < node->files_count; i++) {
        kprint(node->files[i]->name);
        if (i != node->files_count - 1) {
            kprint(", ");
        }
    }
    kprint("\n");
}

static commands_t commands;

void main() {
    isr_install();
    irq_install();

    asm("int $2");
    asm("int $3");

    commands = (commands_t){0};

    init_fs();

    register_command(&commands, SV("HELP"), 0, cmd_help);
    register_command(&commands, SV("CLEAR"), 0, cmd_clear);
    register_command(&commands, SV("ECHO"), -1, cmd_echo);
    register_command(&commands, SV("LS"), 0, cmd_ls);

    clear_screen();

    kprint("WELCOME TO PLUH OS\n\n");
    kprint(">>> ");
}

void user_input(char *input) {
    if (strcmp(input, "END")) {
        kprint("STOPPING THE CPU. BYE!\n");
        asm volatile("hlt");
    } else {
        handle_command(&commands, input);
        kprint("\n>>> ");
    }
}