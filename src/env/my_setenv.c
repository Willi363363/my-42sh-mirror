/*
** EPITECH PROJECT, 2025
** my_setenv.c
** File description:
** Set an environment variable in the shell's environment
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "global.h"
#include "shell.h"

static int replace_env_var(shell_parameters_t *shell, const char *env_str)
{
    char *tmp = strdup(env_str);
    char *name = strtok(tmp, "=");

    for (int i = 0; shell->env[i]; i++) {
        if (strncmp(name, shell->env[i], strlen(name)) == 0
            && shell->env[i][strlen(name)] == '=') {
            free(shell->env[i]);
            shell->env[i] = strdup(env_str);
            free(tmp);
            return SUCCESS;
        }
    }
    free(tmp);
    return EXIT_FAIL;
}

static int add_env_var(shell_parameters_t *shell, const char *env_str)
{
    int i = 0;
    char **new_env = NULL;

    for (; shell->env[i]; i++)
        ;
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return EXIT_FAIL;
    for (int j = 0; j < i; j++)
        new_env[j] = shell->env[j];
    new_env[i] = strdup(env_str);
    new_env[i + 1] = NULL;
    free(shell->env);
    shell->env = new_env;
    return SUCCESS;
}

int my_setenv(shell_parameters_t *shell, const char *var, const char *value)
{
    char *env_str = NULL;
    int ret = 0;
    size_t len = strlen(var) + (value ? strlen(value) : 0) + 2;

    env_str = malloc(len);
    if (!env_str)
        return EXIT_FAIL;
    if (value)
        snprintf(env_str, len, "%s=%s", var, value);
    else
        snprintf(env_str, len, "%s=", var);
    if (replace_env_var(shell, env_str) == EXIT_FAIL)
        ret = add_env_var(shell, env_str);
    free(env_str);
    return ret;
}
