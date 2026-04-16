/*
** EPITECH PROJECT, 2025
** history.c
** File description:
** This file contains the history builtin.
*/
#include "global.h"

static void write_full_cmd(shell_parameters_t *shell, int fd, int line_n)
{
    char bck = '\n';

    for (int i = 0; shell->command[i] != NULL; i++)
        write(fd, shell->command[i], strlen(shell->command[i]));
    write(fd, &bck, 1);
}

static int check_history_ll(int fd, int *line_nb, char *cmd)
{
    char *line;
    size_t line_lenght;
    char *old = NULL;
    FILE *file = fopen("history", "r");

    if (!file)
        return EXIT_FAIL;
    for ((*line_nb) = 0; getline(&line, &line_lenght, file) != -1;
        ++(*line_nb)) {
        if (old && (*line_nb) > 1)
            free(old);
        old = my_strdup(line);
        if (!old)
            return EXIT_FAIL;
    }
    fclose(file);
    if (strcmp(old, cmd) == 0)
        return 1;
    return SUCCESS;
}

void push_to_history(shell_parameters_t *shell)
{
    int fd;
    struct stat s;
    int history_exists = 1;
    int line_nb = 0;
    char *last_line = NULL;

    if (stat("history", &s) == -1)
        history_exists = 0;
    fd = open("history", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (history_exists &&
        check_history_ll(fd, &line_nb, shell->command[1]) != 0)
        return;
    write_full_cmd(shell, fd, line_nb);
    close(fd);
}
