/*
** EPITECH PROJECT, 2026
** exec_and.c
** File description:
** Execute an AND node in the AST.
*/
#include "execution.h"
#include "global.h"
#include "parsing.h"
#include "shell.h"
#include "utils.h"

int exec_and(ast_node_t *node, shell_parameters_t *shell)
{
    if (node->left == NULL || node->right == NULL) {
        my_putstr_error("Invalid null command.\n");
        shell->last_exit_code = EXIT_FAIL;
        return EXIT_FAIL;
    }
    if (run_ast(node->left, shell) == SUCCESS)
        return run_ast(node->right, shell);
    return EXIT_FAIL;
}
