/*
** EPITECH PROJECT, 2026
** builtins/misc.h
** File description:
** Misc builtins header file
*/
#ifndef MISC_H
    #define MISC_H
    #include "shell.h"

int builtin_history(shell_parameters_t *shell);
int builtin_where(shell_parameters_t *shell);
int builtin_which(shell_parameters_t *shell);
int builtin_repeat(shell_parameters_t *shell, char **args);
int builtin_cd(shell_parameters_t *shell);
int exec_misc_builtins(char *line, shell_parameters_t *shell);
int cd_to_path(shell_parameters_t *shell, const char *path);

#endif /* !MISC_H */
