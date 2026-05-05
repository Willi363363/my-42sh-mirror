/*
** EPITECH PROJECT, 2026
** shell_clean.c
** File description:
** Clean the shell struct
*/
#include "global.h"
#include "shell.h"
#include "utils.h"

int shell_clean(shell_parameters_t *shell)
{
    if (shell->env != NULL) {
        for (int i = 0; shell->env[i] != NULL; i++)
            safe_free((void **)&shell->env[i]);
        safe_free((void **)&shell->env);
    }
    if (shell->paths != NULL) {
        for (int i = 0; shell->paths[i] != NULL; i++)
            safe_free((void **)&shell->paths[i]);
        safe_free((void **)&shell->paths);
    }
    if (shell->command != NULL) {
        for (int i = 0; shell->command[i] != NULL; i++)
            safe_free((void **)&shell->command[i]);
        safe_free((void **)&shell->command);
    }
    safe_free((void **)&shell->line);
    safe_free((void **)&shell->command_real_path);
    return SUCCESS;
}
