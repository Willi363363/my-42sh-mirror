/*
** EPITECH PROJECT, 2025
** env_parse.c
** File description:
** This file contains all my environement parse functions.
*/
#include "../includes/global.h"

char **duplicate_env(char **env)
{
    int count = 0;
    char **new_env = NULL;

    for (; env[count] != NULL; count++);
    new_env = malloc(sizeof(char *) * (count + 1));
    if (new_env == NULL)
        return env;
    for (int i = 0; i < count; i++)
        new_env[i] = my_strdup(env[i]);
    new_env[count] = NULL;
    return new_env;
}

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
    char *line_copy = my_strdup(line + 5);
    int path_count = count_paths(line_copy);
    int i = 0;

    shell->paths = malloc((path_count + 1) * sizeof(char *));
    if (shell->paths == NULL)
        return;
    tempo = strtok(line_copy, ":");
    while (tempo != NULL) {
        shell->paths[i] = my_strdup(tempo);
        i++;
        tempo = strtok(NULL, ":");
    }
    shell->paths[i] = NULL;
    free(line_copy);
}

void create_paths(shell_parameters_t *shell)
{
    for (int i = 0; shell->env[i] != NULL; i++)
        if (my_strncmp(shell->env[i], "PATH=", 5) == 0)
            tokenise_path(shell->env[i], shell);
}

char *get_pwd(char **env)
{
    char *str = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "PWD=", 4) == 0)
            str = crop_str_skip(env[i], 4);
    }
    return str;
}
