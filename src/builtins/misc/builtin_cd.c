/*
** EPITECH PROJECT, 2026
** builtin_cd.c
** File description:
** Builtin cd command implementation
*/
#include <string.h>
#include <stdio.h>
#include "builtins/misc.h"
#include "env.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static int cd_to_home(shell_parameters_t *shell)
{
    char *home = my_getenv(shell->env, "HOME");

    if (!home) {
        my_putstr_error("cd: No home directory.\n");
        return COMMAND_ERROR;
    }
    return cd_to_path(shell, home);
}

static int cd_to_oldpwd(shell_parameters_t *shell)
{
    char *oldpwd = my_getenv(shell->env, "OLDPWD");

    if (!oldpwd) {
        my_putstr_error("cd: OLDPWD not set\n");
        return COMMAND_ERROR;
    }
    return cd_to_path(shell, oldpwd);
}

int builtin_cd(shell_parameters_t *shell)
{
    char **cmd = shell->command;

    if (!cmd[1] || strcmp(cmd[1], "~") == 0)
        return cd_to_home(shell);
    if (strcmp(cmd[1], "-") == 0)
        return cd_to_oldpwd(shell);
    if (cmd[2]) {
        my_putstr_error("cd: Too many arguments.\n");
        shell->last_exit_code = EXIT_FAIL;
        return COMMAND_ERROR;
    }
    return cd_to_path(shell, cmd[1]);
}
