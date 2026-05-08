/*
** EPITECH PROJECT, 2026
** shell_init.c
** File description:
** Initialize the shell parameters and environment variables
*/
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "global.h"
#include "shell.h"

void shell_init(shell_parameters_t *shell, char **env)
{
    shell->status = RUNNING;
    shell->env = duplicate_env(env);
    for (size_t i = 0; i < sizeof(shell->pwd); i++)
        shell->pwd[i] = '\0';
    shell->line = NULL;
    shell->line_lenght = 0;
    shell->nread = 0;
    shell->last_exit_code = 0;
    shell->command_found = -1;
    shell->command = NULL;
    shell->command_real_path = NULL;
    shell->aliases = NULL;
}
