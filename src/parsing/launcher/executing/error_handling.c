/*
** EPITECH PROJECT, 2025
** error_handling.c
** File description:
** Handle errors during execution.
*/
#include "../includes/global.h"

int redir_errors(ast_node_t *node, shell_parameters_t *shell)
{
    if (node->left == NULL || node->right == NULL) {
        my_putstr_error("Missing name for redirect.\n");
        shell->last_exit_code = EXIT_FAIL;
        return EXIT_FAIL;
    }
    return SUCCESS;
}

int redir_path_error(void)
{
    my_putstr_error("Permission denied or invalid path\n");
    return EXIT_FAIL;
}

int heredoc_pipe_error(int *fd)
{
    if (pipe(fd) == -1) {
        my_putstr_error("Failed to pipe.\n");
        return EXIT_FAIL;
    }
    return SUCCESS;
}
