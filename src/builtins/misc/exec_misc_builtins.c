/*
** EPITECH PROJECT, 2025
** exec_misc_builtins.c
** File description:
** Exec the misc builtins
*/
#include <stdio.h>
#include <string.h>
#include "builtins/misc.h"
#include "cod_editor.h"
#include "global.h"

static int echo_last_exit_status(shell_parameters_t *shell)
{
    printf("%d\n", shell->last_exit_code);
    shell->last_exit_code = 0;
    return COMMAND_FOUND;
}

static int has_command_suffix(char *line, int index)
{
    return line[index] == '\n' || line[index] == '\0' || line[index] == ' ';
}

static int is_command(char *line, char *command)
{
    return strncmp(line, command, strlen(command)) == 0;
}

static int handle_repeat(char *line, shell_parameters_t *shell)
{
    if (is_command(line, "repeat") && has_command_suffix(line, 6))
        return builtin_repeat(shell, shell->command);
    return SUCCESS;
}

static int handle_misc_base(char *line, shell_parameters_t *shell)
{
    if (strcmp(line, "exit") == 0) {
        shell->status = 0;
        shell->last_exit_code = SUCCESS;
        return COMMAND_FOUND;
    }
    if (strncmp(line, "echo $?", 7) == 0
        && (line[7] == '\n' || line[7] == '\0'))
        return echo_last_exit_status(shell);
    if (strncmp(line, "cod", 3) == 0 && has_command_suffix(line, 3))
        return launch_cod_editor(shell);
    return SUCCESS;
}

static int handle_misc_lookup(char *line, shell_parameters_t *shell)
{
    if (is_command(line, "history") && has_command_suffix(line, 7))
        return builtin_history(shell);
    if (is_command(line, "where") && has_command_suffix(line, 5))
        return builtin_where(shell);
    if (is_command(line, "which") && has_command_suffix(line, 5))
        return builtin_which(shell);
    if (is_command(line, "cd") && has_command_suffix(line, 2))
        return builtin_cd(shell);
    if (is_command(line, "alias") && has_command_suffix(line, 5))
        return builtin_alias(shell);
    return handle_repeat(line, shell);
}

int exec_misc_builtins(char *line, shell_parameters_t *shell)
{
    int status = SUCCESS;

    if (shell->command_found == SUCCESS)
        return SUCCESS;
    status = handle_misc_base(line, shell);
    if (status != SUCCESS)
        return status;
    status = handle_misc_lookup(line, shell);
    if (status != SUCCESS)
        return status;
    return SUCCESS;
}
