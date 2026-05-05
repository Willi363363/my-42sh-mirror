/*
** EPITECH PROJECT, 2026
** exec_sequence.c
** File description:
** Execute a sequence node in the AST.
*/
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include "execution.h"
#include "global.h"
#include "parsing.h"
#include "shell.h"

int exec_sequence(ast_node_t *node, shell_parameters_t *shell)
{
    int result = SUCCESS;

    if (node->left != NULL)
        result = run_ast(node->left, shell);
    if (node->right != NULL)
        result = run_ast(node->right, shell);
    return result;
}
