/*
** EPITECH PROJECT, 2026
** exec_redir_append.c
** File description:
** Execute a redirection append node in the AST.
*/
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include "execution.h"
#include "global.h"
#include "parsing.h"
#include "shell.h"

int exec_redir_append(ast_node_t *node, shell_parameters_t *shell)
{
    int fd;

    if (redir_errors(node, shell) == EXIT_FAIL)
        return EXIT_FAIL;
    fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        redir_path_error();
        return EXIT_FAIL;
    }
    return fork_and_exec(fd, STDOUT_FILENO, node, shell);
}
