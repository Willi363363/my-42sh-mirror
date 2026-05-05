/*
** EPITECH PROJECT, 2026
** exec_heredoc.c
** File description:
** Execute a heredoc node in the AST.
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "execution.h"
#include "global.h"
#include "parsing.h"
#include "shell.h"
#include "utils.h"

static int wait_and_set(shell_parameters_t *shell, pid_t child)
{
    int status;

    waitpid(child, &status, 0);
    shell->last_exit_code = WEXITSTATUS(status);
    return WEXITSTATUS(status);
}

static void kill_entry_char(char *str)
{
    size_t len = 0;

    if (!str)
        return;
    len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

static int fill_heredoc(int *fd, ast_node_t *node)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        kill_entry_char(line);
        if (strcmp(line, node->right->args[0]) == 0)
            break;
        write(fd[1], line, strlen(line));
        write(fd[1], "\n", 1);
    }
    free(line);
    close(fd[1]);
    return SUCCESS;
}

static int heredoc_child(ast_node_t *node, shell_parameters_t *shell, int *fd)
{
    pid_t child;

    child = fork();
    if (child == -1)
        return EXIT_FAIL;
    if (child == 0) {
        if (safe_dup2(fd[0], STDIN_FILENO) == EXIT_FAIL) {
            close(fd[0]);
            exit(EXIT_FAIL);
        }
        close(fd[0]);
        exit(run_ast(node->left, shell));
    }
    close(fd[0]);
    return wait_and_set(shell, child);
}

int exec_redir_heredoc(ast_node_t *node, shell_parameters_t *shell)
{
    int fd[2];

    if (redir_errors(node, shell) == EXIT_FAIL)
        return EXIT_FAIL;
    if (pipe(fd) == -1)
        return EXIT_FAIL;
    if (fill_heredoc(fd, node) == EXIT_FAIL)
        return EXIT_FAIL;
    return heredoc_child(node, shell, fd);
}
