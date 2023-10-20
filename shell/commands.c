#include <common/common.h>
#include <drivers/screen.h>
#include <shell/command.h>
#include <shell/commands.h>
#include <stdint.h>
#include <string.h>

void cmd_help(commands_t *commands, string *args) {
    UNUSED(args);
    kprint("AVAILABLE COMMANDS (");
    kprint(sitoa(commands->commands_count));
    kprint("):\n");
    for (int i = 0; i < commands->commands_count; i++) {
        kprint(" - ");
        kprint(commands->commands[i].name.data);
        kprint("\n");
    }
}

void cmd_clear(commands_t *commands, string *args) {
    UNUSED(commands);
    UNUSED(args);
    clear_screen();
}

void cmd_echo(commands_t *commands, string *args) {
    UNUSED(commands);
    kprint(args->data);
    kprint("\n");
}

void cmd_ls(commands_t *commands, string *args) {
    UNUSED(commands);
    UNUSED(args);
    PANIC("Unimplemented");
}