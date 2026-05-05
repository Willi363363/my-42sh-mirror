/*
** EPITECH PROJECT, 2026
** get_history_path.c
** File description:
** Get the path to the history file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "history.h"
#include "shell.h"

char *get_history_path(shell_parameters_t *shell)
{
    char *home = my_getenv(shell->env, "HOME");
    char *history_path = NULL;

    if (!home)
        return NULL;
    history_path = malloc(strlen(home) + strlen(HISTORY_FILE_NAME) + 2);
    if (!history_path)
        return NULL;
    sprintf(history_path, "%s/%s", home, HISTORY_FILE_NAME);
    return history_path;
}
