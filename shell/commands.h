#ifndef _PLUH_OS__SHELL__COMMANDS_H_
#define _PLUH_OS__SHELL__COMMANDS_H_

#include <common/common.h>
#include <shell/command.h>
#include <stdint.h>
#include <string.h>

void cmd_help(commands_t *commands, string *args);
void cmd_clear(commands_t *commands, string *args);
void cmd_echo(commands_t *commands, string *args);
void cmd_ls(commands_t *commands, string *args);

#endif // _PLUH_OS__SHELL__COMMANDS_H_