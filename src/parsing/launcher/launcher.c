/*
** EPITECH PROJECT, 2025
** str_to_word_array.c
** File description:
** Transform a char * into a word char **.
*/
#include "../includes/global.h"

static int search_to_run_2(ast_node_t *node, shell_parameters_t *shell)
{
    if (node->type == NODE_SUBSHELL)
        return exec_subshell(node, shell);
    if (node->type == NODE_REDIR_IN)
        return exec_redir_in(node, shell);
    if (node->type == NODE_REDIR_HEREDOC)
        return exec_redir_heredoc(node, shell);
    if (node->type == NODE_REDIR_OUT)
        return exec_redir_out(node, shell);
    if (node->type == NODE_REDIR_APPEND)
        return exec_redir_append(node, shell);
    return EXIT_FAIL;
}

static int search_to_run_1(ast_node_t *node, shell_parameters_t *shell)
{
    if (node->type == NODE_COMMAND)
        return exec_command(node, shell);
    if (node->type == NODE_PIPE)
        return exec_pipe(node, shell);
    if (node->type == NODE_AND)
        return exec_and(node, shell);
    if (node->type == NODE_OR)
        return exec_or(node, shell);
    if (node->type == NODE_SEQUENCE)
        return exec_sequence(node, shell);
    return search_to_run_2(node, shell);
}

int run_ast(ast_node_t *node, shell_parameters_t *shell)
{
    if (!node)
        return SUCCESS;
    return search_to_run_1(node, shell);
}
