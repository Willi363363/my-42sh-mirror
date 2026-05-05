/*
** EPITECH PROJECT, 2025
** env_extract_path.c
** File description:
** Extract the PATH variable from the env and tokenise it into an array of paths
*/
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "shell.h"

static int count_paths(char *line)
{
    int count = 1;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ':')
            count++;
    }
    return count;
}

static void tokenise_path(char *line, shell_parameters_t *shell)
{
    char *tempo = NULL;
    char *line_copy = strdup(line + 5);
    int path_count = count_paths(line_copy);
    int i = 0;

    shell->paths = malloc((path_count + 1) * sizeof(char *));
    if (shell->paths == NULL)
        return;
    tempo = strtok(line_copy, ":");
    while (tempo != NULL) {
        shell->paths[i] = strdup(tempo);
        i++;
        tempo = strtok(NULL, ":");
    }
    shell->paths[i] = NULL;
    free(line_copy);
}

void env_extract_paths(shell_parameters_t *shell)
{
    for (int i = 0; shell->env[i] != NULL; i++)
        if (strncmp(shell->env[i], "PATH=", 5) == 0)
            tokenise_path(shell->env[i], shell);
}
