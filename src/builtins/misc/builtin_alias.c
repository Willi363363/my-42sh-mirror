/*
** EPITECH PROJECT, 2026
** builtin_cd.c
** File description:
** Builtin cd command implementation
*/
#include <stdio.h>
#include <string.h>
#include "alias.h"
#include "builtins/misc.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static int print_alias(shell_parameters_t *shell, char *name)
{
    alias_t *alias = NULL;

    for (size_t i = 0; shell->aliases && shell->aliases[i].name; i++) {
        if (strcmp(shell->aliases[i].name, name) == 0) {
            alias = &shell->aliases[i];
            break;
        }
    }
    if (!alias)
        return COMMAND_FOUND;
    for (size_t i = 0; alias->value && alias->value[i]; i++) {
        printf("%s%c", alias->value[i], alias->value[i + 1] ? ' ' : '\n');
    }
    return COMMAND_FOUND;
}

int builtin_alias(shell_parameters_t *shell)
{
    char **cmd = shell->command;
    size_t argc = word_array_len(cmd);

    shell->last_exit_code = SUCCESS;
    if (argc != 2 && argc != 3)
        return COMMAND_FOUND;
    if (argc == 2)
        return print_alias(shell, cmd[1]);
    if (aliases_push(&shell->aliases, cmd[1], cmd[2]) == EXIT_FAIL) {
        fprintf(stderr, "alias: failed to create alias\n");
        shell->last_exit_code = EXIT_FAIL;
        return COMMAND_FOUND;
    }
    shell->last_exit_code = SUCCESS;
    return COMMAND_FOUND;
}
