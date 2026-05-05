/*
** EPITECH PROJECT, 2026
** fork_and_exec.c
** File description:
** Fork a child process and execute a command
*/
#include <stdlib.h>
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

int fork_and_exec(int fd,
    int target,
    ast_node_t *node,
    shell_parameters_t *shell)
{
    pid_t child;

    child = fork();
    if (child == -1) {
        close(fd);
        return EXIT_FAIL;
    }
    if (child == 0) {
        if (safe_dup2(fd, target) == EXIT_FAIL) {
            close(fd);
            exit(EXIT_FAIL);
        }
        close(fd);
        exit(run_ast(node->left, shell));
    }
    close(fd);
    return wait_and_set(shell, child);
}
