/*
** EPITECH PROJECT, 2025
** free_struct.c
** File description:
** This file's purpose is to free my shell struct and its fields.
*/
#include "./../../includes/global.h"

int clean_and_exit(shell_parameters_t *shell)
{
    if (shell->env != NULL) {
        for (int i = 0; shell->env[i] != NULL; i++)
            my_safe_free((void **)&shell->env[i]);
        my_safe_free((void **)&shell->env);
    }
    if (shell->paths != NULL) {
        for (int i = 0; shell->paths[i] != NULL; i++)
            my_safe_free((void **)&shell->paths[i]);
        my_safe_free((void **)&shell->paths);
    }
    if (shell->command != NULL) {
        for (int i = 0; shell->command[i] != NULL; i++)
            my_safe_free((void **)&shell->command[i]);
        my_safe_free((void **)&shell->command);
    }
    my_safe_free((void **)&shell->line);
    my_safe_free((void **)&shell->command_real_path);
    return SUCCESS;
}

void clean_every_iteration(shell_parameters_t *shell)
{
    if (shell->command != NULL) {
        for (int i = 0; shell->command[i] != NULL; i++)
            my_safe_free((void **)&shell->command[i]);
        my_safe_free((void **)&shell->command);
    }
    my_safe_free((void **)&shell->command_real_path);
}

void free_paths(shell_parameters_t *shell)
{
    for (int i = 0; shell->paths[i] != NULL; i++)
        free(shell->paths[i]);
}

void free_lexer(lexer_t **lexer)
{
    return;
}

void free_ast(ast_node_t *ast)
{
    return;
}
