/*
** EPITECH PROJECT, 2025
** env_expand.c
** File description:
** Expand environment variables inside AST command arguments.
*/
#include "../includes/global.h"

static char *find_env_value(shell_parameters_t *shell, char *name)
{
    int len = my_strlen(name);

    if (len == 0)
        return NULL;
    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], name, len) == 0 &&
            shell->env[i][len] == '=')
            return shell->env[i] + len + 1;
    }
    return NULL;
}

static char *expand_single_env(char *arg, shell_parameters_t *shell)
{
    char *value = NULL;

    if (!arg || arg[0] != '$' || my_strcmp(arg, "$?") == 0)
        return my_strdup(arg);
    value = find_env_value(shell, arg + 1);
    if (value)
        return my_strdup(value);
    return my_strdup("");
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

void expand_ast_env(ast_node_t *node, shell_parameters_t *shell)
{
    if (!node || !shell || !shell->env)
        return;
    if (node->type == NODE_COMMAND)
        expand_command_args(node->args, shell);
    expand_ast_env(node->left, shell);
    expand_ast_env(node->right, shell);
    expand_ast_env(node->payload, shell);
}
