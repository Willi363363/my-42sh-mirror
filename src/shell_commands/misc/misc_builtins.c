/*
** EPITECH PROJECT, 2025
** misc_builtins.c
** File description:
** This file contains some built in functions.
*/
#include "../../../includes/global.h"

static int echo_last_exit_status(shell_parameters_t *shell)
{
    my_put_nbr(shell->last_exit_code);
    my_putchar('\n');
    shell->last_exit_code = 0;
    return COMMAND_FOUND;
}

int misc_cmds_assert(char *line, shell_parameters_t *shell)
{
    if (shell->command_found == SUCCESS)
        return SUCCESS;
    if (my_strcmp(line, "exit\n") == 0) {
        clean_and_exit(shell);
        exit(SUCCESS);
    }
    if (my_strncmp(line, "echo $?", 7) == 0 &&
        (line[7] == '\n' || line[7] == '\0'))
        return echo_last_exit_status(shell);
    if (my_strncmp(line, "cod", 3) == 0 &&
        (line[3] == '\n' || line[3] == '\0' || line[3] == ' '))
        return cod(shell);
    if (my_strcmp(line, "history") == 0 &&
        (line[7] == '\n' || line[7] == '\0' || line[7] == ' '))
        return display_history(shell);
    return SUCCESS;
}
