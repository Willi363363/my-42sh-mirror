/*
** EPITECH PROJECT, 2026
** builtins/env.h
** File description:
** Environment variables related builtins header file
*/
#ifndef ENV_BUILTINS_H
    #define ENV_BUILTINS_H
    #include "shell.h"

int builtin_setenv(shell_parameters_t *shell);
int builtin_unsetenv(shell_parameters_t *shell);
int exec_env_builtins(shell_parameters_t *shell);

#endif /* !ENV_BUILTINS_H */
