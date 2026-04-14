/*
** EPITECH PROJECT, 2025
** env_cmds.c
** File description:
** This file contains all my envs commands functions.
*/
#include "../../../includes/global.h"

static int print_env(shell_parameters_t *shell)
{
    int ret = 0;

    if (my_tablen(shell->command) != 1) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error("setenv: Too many arguments.\n");
        return COMMAND_ERROR;
    }
    for (int i = 0; shell->env[i] != NULL; i++) {
        ret = my_putstr(shell->env[i]);
        my_putchar('\n');
    }
    shell->last_exit_code = ret;
    shell->command_found = 1;
    return COMMAND_FOUND;
}

int env_cmds_assert(char *line, shell_parameters_t *shell)
{
    if (shell->command_found == SUCCESS)
        return SUCCESS;
    if (my_strncmp(line, "env", 3) == 0)
        return print_env(shell);
    if (my_strncmp(line, "setenv", 6) == 0 &&
        (line[6] == '\n' || line[6] == '\0'))
        return print_env(shell);
    if (my_strncmp(line, "setenv ", 7) == 0)
        return set_env(shell);
    if (my_strncmp(line, "unsetenv ", 9) == 0)
        return unset_env(shell);
    return SUCCESS;
}
