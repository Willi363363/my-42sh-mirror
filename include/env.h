/*
** EPITECH PROJECT, 2026
** env.h
** File description:
** Environment variables related functions header file
*/
#ifndef ENV_H
    #define ENV_H
    #include "shell.h"

char **duplicate_env(char **env);
void env_extract_paths(shell_parameters_t *shell);
int my_setenv(shell_parameters_t *shell, const char *var, const char *value);
int my_unsetenv(shell_parameters_t *shell, const char *var);
char *my_getenv(char **env, const char *name);

#endif /* !ENV_H */
