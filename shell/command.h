#ifndef _PLUH_OS__SHELL__COMMAND_H_
#define _PLUH_OS__SHELL__COMMAND_H_

#include <common/common.h>
#include <libc/stdint.h>
#include <libc/string.h>

#define COMMANDS_MAX 256

typedef struct commands_t commands_t;

typedef void (*command_handler_t)(struct commands_t *, string *);

typedef struct {
    string name;
    uint32_t arity;
    command_handler_t handler;
} command_t;

struct commands_t {
    command_t commands[COMMANDS_MAX];
    uint32_t commands_count;
};

void register_command(commands_t *commands, string name, uint32_t arity,
                      command_handler_t handler);
void handle_command(commands_t *commands, char *input);

#endif // _PLUH_OS__SHELL__COMMAND_H_