/*
** EPITECH PROJECT, 2025
** exec.c
** File description:
** Functions to execute commands and handle redirections.
*/

#include "../includes/global.h"

static int wait_and_set(shell_parameters_t *shell, pid_t child)
{
    int status;

    waitpid(child, &status, 0);
    shell->last_exit_code = WEXITSTATUS(status);
    return WEXITSTATUS(status);
}

static int fork_and_exec(int fd, int target,
    ast_node_t *node, shell_parameters_t *shell)
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

int exec_redir_in(ast_node_t *node, shell_parameters_t *shell)
{
    int fd;

    if (redir_errors(node, shell) == EXIT_FAIL)
        return EXIT_FAIL;
    fd = open(node->right->args[0], O_RDONLY);
    if (fd == -1) {
        redir_path_error();
        return EXIT_FAIL;
    }
    return fork_and_exec(fd, STDIN_FILENO, node, shell);
}

int exec_redir_out(ast_node_t *node, shell_parameters_t *shell)
{
    int fd;

    if (redir_errors(node, shell) == EXIT_FAIL)
        return EXIT_FAIL;
    fd = open(node->right->args[0],
        O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        redir_path_error();
        return EXIT_FAIL;
    }
    return fork_and_exec(fd, STDOUT_FILENO, node, shell);
}

int exec_redir_append(ast_node_t *node, shell_parameters_t *shell)
{
    int fd;

    if (redir_errors(node, shell) == EXIT_FAIL)
        return EXIT_FAIL;
    fd = open(node->right->args[0],
        O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        redir_path_error();
        return EXIT_FAIL;
    }
    return fork_and_exec(fd, STDOUT_FILENO, node, shell);
}

static int heredoc_child(ast_node_t *node,
    shell_parameters_t *shell, int *fd)
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

static void kill_entry_char(char *str)
{
    size_t len = 0;

    if (!str)
        return;
    len = my_strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

static int fill_heredoc(int *fd, ast_node_t *node)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        kill_entry_char(line);
        if (my_strcmp(line, node->right->args[0]) == 0)
            break;
        write(fd[1], line, my_strlen(line));
        write(fd[1], "\n", 1);
    }
    free(line);
    close(fd[1]);
    return SUCCESS;
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

int exec_subshell(ast_node_t *node, shell_parameters_t *shell)
{
    (void)node;
    (void)shell;
    return SUCCESS;
}
