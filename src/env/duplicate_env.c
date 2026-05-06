/*
** EPITECH PROJECT, 2025
** duplicate_env.c
** File description:
** Duplicate the environment variables array
*/
#include <stdlib.h>
#include <string.h>
#include "env.h"

char **duplicate_env(char **env)
{
    int count = 0;
    char **new_env = NULL;

    if (env == NULL)
        return NULL;
    for (; env[count] != NULL; count++)
        ;
    new_env = malloc(sizeof(char *) * (count + 1));
    if (new_env == NULL)
        return env;
    for (int i = 0; i < count; i++)
        new_env[i] = strdup(env[i]);
    new_env[count] = NULL;
    return new_env;
}
