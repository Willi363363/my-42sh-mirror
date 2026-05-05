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
    int ret = 0;

    if (len < 2) {
        set_error(shell, "unsetenv: Too few arguments.\n");
        return COMMAND_ERROR;
    }
    for (int i = 1; shell->command[i]; i++) {
        if (my_unsetenv(shell, shell->command[i]) == EXIT_FAIL)
            ret = EXIT_FAIL;
    }
    shell->last_exit_code = ret;
    return COMMAND_FOUND;
}
