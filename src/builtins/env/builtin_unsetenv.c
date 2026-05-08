/*
** EPITECH PROJECT, 2025
** builtin_unsetenv.c
** File description:
** unsetenv builtin
*/
#include "env.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static void set_error(shell_parameters_t *shell, const char *msg)
{
    my_putstr_error(msg);
    shell->last_exit_code = EXIT_FAIL;
}

int builtin_unsetenv(shell_parameters_t *shell)
{
    int len = my_tablen(shell->command);

    if (len < 2) {
        set_error(shell, "unsetenv: Too few arguments.\n");
        return COMMAND_FOUND;
    }
    for (int i = 1; shell->command[i] != NULL; i++) {
        my_unsetenv(shell, shell->command[i]);
    }
    shell->last_exit_code = 0;
    return COMMAND_FOUND;
}
