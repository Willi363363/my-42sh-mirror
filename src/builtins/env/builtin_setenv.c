/*
** EPITECH PROJECT, 2025
** builtin_setenv.c
** File description:
** setenv builtin command
*/
#include "env.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static void set_error(shell_parameters_t *shell, const char *msg)
{
    my_putstr_error(msg);
    shell->last_exit_code = EXIT_FAIL;
    shell->command_found = 1;
}

static int validate_name(shell_parameters_t *shell, char *name)
{
    if (is_alphanums(name) == EXIT_FAIL) {
        set_error(shell,
            "setenv: Variable name must contain alphanumeric characters.\n");
        return EXIT_FAIL;
    }
    return SUCCESS;
}

int builtin_setenv(shell_parameters_t *shell)
{
    int len = my_tablen(shell->command);

    if (len > 3) {
        set_error(shell, "setenv: Too many arguments.\n");
        return COMMAND_FOUND;
    }
    if (len < 2) {
        shell->last_exit_code = 0;
        shell->command_found = 1;
        return COMMAND_FOUND;
    }
    if (validate_name(shell, shell->command[1]) == EXIT_FAIL)
        return COMMAND_FOUND;
    if (len == 2)
        shell->last_exit_code = my_setenv(shell, shell->command[1], NULL);
    else
        shell->last_exit_code =
            my_setenv(shell, shell->command[1], shell->command[2]);
    shell->command_found = 1;
    return COMMAND_FOUND;
}
