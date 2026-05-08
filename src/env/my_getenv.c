/*
** EPITECH PROJECT, 2025
** my_getenv.c
** File description:
** Get an environment variable from the environment array
*/
#include <string.h>
#include "env.h"

char *my_getenv(char **env, const char *name)
{
    size_t name_len = strlen(name);

    if (!env || !name)
        return NULL;
    for (size_t i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
            return env[i] + name_len + 1;
    }
    return NULL;
}
