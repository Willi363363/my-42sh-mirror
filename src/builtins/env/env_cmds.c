/*
** EPITECH PROJECT, 2025
** env_cmds.c
** File description:
** This file contains all my envs commands functions.
*/
#include <stdio.h>
#include <string.h>
#include "builtins/env.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static int print_env(shell_parameters_t *shell)
{
    int ret = 0;

    if (my_tablen(shell->command) != 1) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error("setenv: Too many arguments.\n");
        return COMMAND_ERROR;
    }
    for (int i = 0; shell->env[i] != NULL; i++) {
        printf("%s\n", shell->env[i]);
    }
    shell->last_exit_code = ret;
    shell->command_found = 1;
    return COMMAND_FOUND;
}

int exec_env_builtins(shell_parameters_t *shell)
{
    if (shell->command_found == SUCCESS)
        return SUCCESS;
    if (shell->command == NULL || shell->command[0] == NULL)
        return SUCCESS;
    if (strcmp(shell->command[0], "env") == 0)
        return print_env(shell);
    if (strcmp(shell->command[0], "setenv") == 0)
        return builtin_setenv(shell);
    if (strcmp(shell->command[0], "unsetenv") == 0)
        return builtin_unsetenv(shell);
    return SUCCESS;
}
