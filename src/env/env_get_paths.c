/*
** EPITECH PROJECT, 2025
** env_get_paths.c
** File description:
** Get the PATH environment variable and split it into an array of paths
*/
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "shell.h"
#include "utils.h"

static char **tokenise_path(char *line)
{
    char *tempo = NULL;
    char *line_copy = strdup(line + 5);
    char **paths = NULL;

    if (line_copy == NULL)
        return NULL;
    tempo = strtok(line_copy, ":");
    while (tempo != NULL) {
        word_array_push(&paths, tempo);
        tempo = strtok(NULL, ":");
    }
    free(line_copy);
    return paths;
}

char **env_get_paths(shell_parameters_t *shell)
{
    char *path = my_getenv(shell->env, "PATH");

    if (path)
        return tokenise_path(path);
    return NULL;
}
