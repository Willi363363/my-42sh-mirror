/*
** EPITECH PROJECT, 2026
** exec_or.c
** File description:
** Execute an OR node in the AST.
*/
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include "execution.h"
#include "global.h"
#include "parsing.h"
#include "shell.h"
#include "utils.h"

int exec_or(ast_node_t *node, shell_parameters_t *shell)
{
    if (node->left == NULL || node->right == NULL) {
        my_putstr_error("Invalid null command.\n");
        shell->last_exit_code = EXIT_FAIL;
        return EXIT_FAIL;
    }
    if (run_ast(node->left, shell) != SUCCESS)
        return run_ast(node->right, shell);
    return SUCCESS;
}
