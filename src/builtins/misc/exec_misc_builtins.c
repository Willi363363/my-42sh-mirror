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

static int handle_misc_base(shell_parameters_t *shell)
{
    if (strcmp(shell->command[0], "exit") == 0 && shell->command[1] == NULL) {
        shell->status = 0;
        shell->last_exit_code = SUCCESS;
        return COMMAND_FOUND;
    }
    if (strcmp(shell->command[0], "echo") == 0 && shell->command[1]
        && strcmp(shell->command[1], "$?") == 0 && shell->command[2] == NULL)
        return echo_last_exit_status(shell);
    if (strcmp(shell->command[0], "cod") == 0)
        return launch_cod_editor(shell);
    return SUCCESS;
}

static int handle_misc_lookup(shell_parameters_t *shell)
{
    if (strcmp(shell->command[0], "history") == 0)
        return builtin_history(shell);
    if (strcmp(shell->command[0], "where") == 0)
        return builtin_where(shell);
    if (strcmp(shell->command[0], "which") == 0)
        return builtin_which(shell);
    if (strcmp(shell->command[0], "cd") == 0)
        return builtin_cd(shell);
    if (strcmp(shell->command[0], "alias") == 0)
        return builtin_alias(shell);
    if (strcmp(shell->command[0], "reapeat") == 0)
        return builtin_repeat(shell, shell->command);
    return SUCCESS;
}

int exec_misc_builtins(shell_parameters_t *shell)
{
    int status = SUCCESS;

    if (shell->command_found == SUCCESS)
        return SUCCESS;
    if (shell->command == NULL || shell->command[0] == NULL)
        return SUCCESS;
    status = handle_misc_base(shell);
    if (status != SUCCESS)
        return status;
    status = handle_misc_lookup(shell);
    if (status != SUCCESS)
        return status;
    return SUCCESS;
}
