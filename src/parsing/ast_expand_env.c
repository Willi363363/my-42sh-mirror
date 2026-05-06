/*
** EPITECH PROJECT, 2025
** env_expand.c
** File description:
** Expand environment variables inside AST command arguments.
*/
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "parsing.h"

static char *expand_single_env(char *arg, shell_parameters_t *shell)
{
    char *value = NULL;

    if (!arg || arg[0] != '$' || strcmp(arg, "$?") == 0)
        return strdup(arg);
    value = my_getenv(shell->env, arg + 1);
    if (value)
        return strdup(value);
    return strdup("");
}

static void expand_command_args(char **args, shell_parameters_t *shell)
{
    char *expanded = NULL;

    if (!args)
        return;
    for (int i = 0; args[i] != NULL; i++) {
        expanded = expand_single_env(args[i], shell);
        if (!expanded)
            continue;
        free(args[i]);
        args[i] = expanded;
    }
}

void ast_expand_env(ast_node_t *node, shell_parameters_t *shell)
{
    if (!node || !shell || !shell->env)
        return;
    if (node->type == NODE_COMMAND)
        expand_command_args(node->args, shell);
    ast_expand_env(node->left, shell);
    ast_expand_env(node->right, shell);
    ast_expand_env(node->payload, shell);
}
