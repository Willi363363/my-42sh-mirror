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

static int has_command_suffix(char *line, int index)
{
    return line[index] == '\n' || line[index] == '\0' || line[index] == ' ';
}

static int is_command(char *line, char *command)
{
    return my_strcmp(line, command) == 0;
}

int misc_cmds_assert(char *line, shell_parameters_t *shell)
{
    if (shell->command_found == SUCCESS)
        return SUCCESS;
    if (my_strcmp(line, "exit") == 0) {
        shell->status = 0;
        shell->last_exit_code = SUCCESS;
        return COMMAND_FOUND;
    }
    if (my_strncmp(line, "echo $?", 7) == 0 &&
        (line[7] == '\n' || line[7] == '\0'))
        return echo_last_exit_status(shell);
    if (my_strncmp(line, "cod", 3) == 0 &&
        has_command_suffix(line, 3))
        return cod(shell);
    if (is_command(line, "history") && has_command_suffix(line, 7))
        return display_history(shell);
    if (is_command(line, "where") && has_command_suffix(line, 5))
        return where(shell);
    if (is_command(line, "which") && has_command_suffix(line, 5))
        return which(shell);
    return SUCCESS;
}
