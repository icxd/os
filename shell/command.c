#include <common/common.h>
#include <drivers/screen.h>
#include <libc/stdlib.h>
#include <libc/string.h>
#include <shell/command.h>

void register_command(commands_t *commands, string name, uint32_t arity,
                      command_handler_t handler) {
    commands->commands[commands->commands_count].name = name;
    commands->commands[commands->commands_count].arity = arity;
    commands->commands[commands->commands_count].handler = handler;
    commands->commands_count++;
}

void handle_command(commands_t *commands, char *input) {
    string cmd = SV(input);
    string *args = NULL;

    int space = index_of(cmd.data, ' ');
    if (space != -1) {
        cmd.data[space] = '\0';
        args = (string *)malloc(sizeof(string));
        args->data = cmd.data + space + 1;
        args->size = cmd.size - space - 1;
    }

    for (uint32_t i = 0; i < commands->commands_count; i++) {
        if (strcmp(commands->commands[i].name.data, cmd.data) == 0) {
            if (commands->commands[i].arity == -1) {
                commands->commands[i].handler(commands, args);
                return;
            }
            if (args == NULL && commands->commands[i].arity != 0) {
                kprint("INVALID NUMBER OF ARGUMENTS, EXPECTED ");
                kprint(itoa(commands->commands[i].arity));
                kprint("\n");
                return;
            }
            if (args != NULL && commands->commands[i].arity != args->size) {
                kprint("INVALID NUMBER OF ARGUMENTS, EXPECTED ");
                kprint(itoa(commands->commands[i].arity));
                kprint("\n");
                return;
            }
            commands->commands[i].handler(commands, args);
            return;
        }
    }

    kprint("INVALID COMMAND '");
    kprint(cmd.data);
    kprint("'\n");
}