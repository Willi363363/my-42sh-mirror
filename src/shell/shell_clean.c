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
    if (shell->env != NULL)
        word_array_destroy(&shell->env);
    if (shell->command != NULL)
        word_array_destroy(&shell->command);
    if (shell->aliases != NULL) {
        for (size_t i = 0; shell->aliases[i].name != NULL; i++) {
            safe_free((void **)&shell->aliases[i].name);
            word_array_destroy(&shell->aliases[i].value);
        }
        safe_free((void **)&shell->aliases);
    }
    safe_free((void **)&shell->line);
    safe_free((void **)&shell->command_real_path);
    return SUCCESS;
}
