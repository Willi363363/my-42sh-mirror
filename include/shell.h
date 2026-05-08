/*
** EPITECH PROJECT, 2026
** shell.h
** File description:
** Shell header file
*/
#ifndef SHELL_H
    #define SHELL_H
    #define MAX_PATH_LEN 4096
    #include <stddef.h>
    #include <sys/types.h>
    #include "alias.h"


typedef struct shell_parameters_s {
    int status;
    char **env;
    char pwd[MAX_PATH_LEN];
    char *line;
    size_t line_lenght;
    ssize_t nread;
    int last_exit_code;
    int command_found;
    char **command;
    char *command_real_path;
    alias_t *aliases;
} shell_parameters_t;

void shell_init(shell_parameters_t *shell, char **env);
int shell_clean(shell_parameters_t *shell);
int shell_exec_cmd(shell_parameters_t *shell);

#endif /* !SHELL_H */
