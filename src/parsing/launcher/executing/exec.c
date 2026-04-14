/*
** EPITECH PROJECT, 2025
** str_to_word_array.c
** File description:
** Transform a char * into a word char **.
*/
#include "../includes/global.h"

int exec_subshell(ast_node_t *node, shell_parameters_t *shell)
{
    return SUCCESS;
}

int exec_redir_in(ast_node_t *node, shell_parameters_t *shell)
{
    int fd;
    pid_t child;
    int status;

    if (redir_errors(node, shell) == EXIT_FAIL)
        return EXIT_FAIL;
    fd = open(node->right->args[0], O_RDONLY);
    if (fd == -1)
        redir_path_error();
    child = fork();
    if (child == 0) {
        dup2(fd, STDIN_FILENO);
        close(fd);
        exit(run_ast(node->left, shell));
    }
    close(fd);
    waitpid(child, &status, 0);
    shell->last_exit_code = WEXITSTATUS(status);
    return WEXITSTATUS(status);
}

static int heredoc_childcare(ast_node_t *node,
    shell_parameters_t *shell, int *fd)
{
    pid_t child;
    int status;

    child = fork();
    if (child == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        exit(run_ast(node->left, shell));
    }
    close(fd[0]);
    waitpid(child, &status, 0);
    shell->last_exit_code = WEXITSTATUS(status);
    return status;
}

static void kill_entry_char(char *to_purify)
{
    if (to_purify[my_strlen(to_purify) - 1] == '\n')
        to_purify[my_strlen(to_purify) - 1] = '\0';
}

int exec_redir_heredoc(ast_node_t *node, shell_parameters_t *shell)
{
    int fd[2];
    char *line = NULL;
    size_t line_lenght;

    if (redir_errors(node, shell) == EXIT_FAIL)
        return EXIT_FAIL;
    if (heredoc_pipe_error(fd) == EXIT_FAIL)
        return EXIT_FAIL;
    while (1) {
        if (getline(&line, &line_lenght, stdin) == -1)
            break;
        kill_entry_char(line);
        if (my_strcmp(line, node->right->args[0]) == 0 || line == NULL)
            break;
        write(fd[1], line, my_strlen(line));
        write(fd[1], "\n", 1);
    }
    close(fd[1]);
    return WEXITSTATUS(heredoc_childcare(node, shell, fd));
}

int exec_redir_out(ast_node_t *node, shell_parameters_t *shell)
{
    int fd;
    pid_t child;
    int status;

    if (redir_errors(node, shell) == EXIT_FAIL)
        return EXIT_FAIL;
    fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        redir_path_error();
    child = fork();
    if (child == 0) {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        exit(run_ast(node->left, shell));
    }
    close(fd);
    waitpid(child, &status, 0);
    shell->last_exit_code = WEXITSTATUS(status);
    return WEXITSTATUS(status);
}

int exec_redir_append(ast_node_t *node, shell_parameters_t *shell)
{
    int fd;
    pid_t child;
    int status;

    if (redir_errors(node, shell) == EXIT_FAIL)
        return EXIT_FAIL;
    fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        redir_path_error();
    child = fork();
    if (child == 0) {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        exit(run_ast(node->left, shell));
    }
    close(fd);
    waitpid(child, &status, 0);
    shell->last_exit_code = WEXITSTATUS(status);
    return WEXITSTATUS(status);
}
