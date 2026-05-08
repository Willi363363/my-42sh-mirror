/*
** EPITECH PROJECT, 2026
** shell_exec_cmd.c
** File description:
** Execute a command in the shell
*/
#include "builtins/env.h"
#include "builtins/misc.h"
#include "execution.h"
#include "expansion.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static void command_not_found(shell_parameters_t *shell, char *command)
{
    my_putstr_error(command);
    my_putstr_error(": Command not found.\n");
    shell->last_exit_code = EXIT_FAIL;
}

int shell_exec_cmd(shell_parameters_t *shell)
{
    int found = 0;

    apply_expansions(shell);
    found = exec_misc_builtins(shell);
    if (found == 0 && found != COMMAND_ERROR)
        found = exec_system_cmd(shell);
    if (found == 0 && found != COMMAND_ERROR)
        found = exec_env_builtins(shell);
    if (found == 0 && found != COMMAND_ERROR)
        found = exec_own_files_cmd(shell);
    if (found == COMMAND_FOUND || found == COMMAND_ERROR)
        return SUCCESS;
    command_not_found(shell, shell->command[0]);
    return EXIT_FAIL;
}
