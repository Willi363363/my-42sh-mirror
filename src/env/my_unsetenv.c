/*
** EPITECH PROJECT, 2025
** my_unsetenv.c
** File description:
** Unset an environment variable from the shell's environment
*/
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "shell.h"
#include "env.h"

static void shift_left(char **env, int index)
{
    for (int i = index; env[i]; i++)
        env[i] = env[i + 1];
}

int my_unsetenv(shell_parameters_t *shell, const char *var)
{
    size_t len = strlen(var);

    for (int i = 0; shell->env[i]; i++) {
        if (strncmp(shell->env[i], var, len) == 0 &&
            shell->env[i][len] == '=') {
            free(shell->env[i]);
            shift_left(shell->env, i);
            return SUCCESS;
        }
    }
    return EXIT_FAIL;
}
