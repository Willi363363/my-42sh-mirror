/*
** EPITECH PROJECT, 2025
** env_cmds.c
** File description:
** This file contains all my envs commands functions.
*/
#include "../../../includes/global.h"

void move_everyone_and_null(char **tab, int start_i)
{
    int i = start_i + 1;

    if (!(tab[start_i + 1])) {
        tab[start_i] = NULL;
        return;
    }
    for (; tab[i] != NULL; i++) {
        tab[i - 1] = tab[i];
    }
    tab[i - 1] = NULL;
}

static void find_and_exterminate(shell_parameters_t *shell, char *var)
{
    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], var, my_strlen(var)) == 0 &&
            shell->env[i][my_strlen(var)] == '=') {
            free(shell->env[i]);
            move_everyone_and_null(shell->env, i);
            return;
        }
    }
}

int unset_env(shell_parameters_t *shell)
{
    int ret = 0;
    int cmd_len = my_tablen(shell->command);

    if (cmd_len == 1) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error("unsetenv : Too few arguments.\n");
        return COMMAND_ERROR;
    }
    for (int i = 1; shell->command[i] != NULL; i++)
        find_and_exterminate(shell, shell->command[i]);
    shell->last_exit_code = ret;
    return COMMAND_FOUND;
}
