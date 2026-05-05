/*
** EPITECH PROJECT, 2026
** execution.h
** File description:
** Execution header file
*/
#ifndef EXECUTION_H
    #define EXECUTION_H
    #include "shell.h"
    #include "parsing.h"

int run_ast(ast_node_t *node, shell_parameters_t *shell);
int fork_and_exec(int fd,
    int target,
    ast_node_t *node,
    shell_parameters_t *shell);

int exec_and(ast_node_t *node, shell_parameters_t *shell);
int exec_or(ast_node_t *node, shell_parameters_t *shell);
int exec_sequence(ast_node_t *node, shell_parameters_t *shell);
int exec_redir_heredoc(ast_node_t *node, shell_parameters_t *shell);
int exec_redir_in(ast_node_t *node, shell_parameters_t *shell);
int exec_redir_out(ast_node_t *node, shell_parameters_t *shell);
int exec_redir_append(ast_node_t *node, shell_parameters_t *shell);
int exec_subshell(ast_node_t *node, shell_parameters_t *shell);
int exec_command(ast_node_t *node, shell_parameters_t *shell);
int exec_pipe(ast_node_t *node, shell_parameters_t *shell);

int redir_errors(ast_node_t *node, shell_parameters_t *shell);
int redir_path_error(void);
int heredoc_pipe_error(int *fd);

int handle_signal(int status);
int exec_system_cmd(shell_parameters_t *shell);
int exec_own_files_cmd(shell_parameters_t *shell);

#endif /* !EXECUTION_H */
