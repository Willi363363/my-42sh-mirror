/*
** EPITECH PROJECT, 2026
** exec_pipe.c
** File description:
** Execute a pipe node in the AST.
*/
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "execution.h"
#include "global.h"
#include "parsing.h"
#include "shell.h"
#include "utils.h"

static void handle_pipe_childs(ast_node_t *node,
    shell_parameters_t *shell,
    int *fd,
    int *childs)
{
    childs[0] = fork();
    if (childs[0] == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        exit(run_ast(node->left, shell));
    }
    childs[1] = fork();
    if (childs[1] == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        exit(run_ast(node->right, shell));
    }
}

int exec_pipe(ast_node_t *node, shell_parameters_t *shell)
{
    int fd[2];
    pid_t childs[2];
    int status = 0;

    if (node->left == NULL || node->right == NULL) {
        my_putstr_error("Invalid null command.\n");
        shell->last_exit_code = EXIT_FAIL;
        return EXIT_FAIL;
    }
    if (pipe(fd) == -1) {
        my_putstr_error("Failed to pipe.\n");
        return EXIT_FAIL;
    }
    handle_pipe_childs(node, shell, fd, childs);
    close(fd[0]);
    close(fd[1]);
    waitpid(childs[0], &status, 0);
    waitpid(childs[1], &status, 0);
    shell->last_exit_code = WEXITSTATUS(status);
    return WEXITSTATUS(status);
}
