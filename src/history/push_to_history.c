/*
** EPITECH PROJECT, 2025
** push_to_history.c
** File description:
** Push the current command to the history file
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "global.h"
#include "history.h"
#include "shell.h"
#include "utils.h"

static void write_full_cmd(shell_parameters_t *shell, int fd, int line_n)
{
    char bck = '\n';
    char esp = ' ';
    char *line_nb = my_itoa(line_n);

    if (!line_nb)
        return;
    write(fd, line_nb, strlen(line_nb));
    write(fd, &esp, 1);
    write(fd, &esp, 1);
    free(line_nb);
    for (int i = 0; shell->command[i] != NULL; i++) {
        write(fd, shell->command[i], strlen(shell->command[i]));
        if (shell->command[i + 1] != NULL)
            write(fd, &esp, 1);
    }
    write(fd, &bck, 1);
}

static char *build_cmd_string(shell_parameters_t *shell)
{
    char *result = NULL;
    int len = 0;

    for (int i = 0; shell->command[i] != NULL; i++)
        len += strlen(shell->command[i]);
    result = malloc(len + 1);
    if (!result)
        return NULL;
    result[0] = '\0';
    for (int i = 0; shell->command[i] != NULL; i++)
        strcat(result, shell->command[i]);
    return result;
}

static int read_history_file(FILE *file, char **line, int *line_nb)
{
    size_t len = 0;

    while (getline(line, &len, file) != -1) {
        (*line)[len - 1] = '\0';
        (*line_nb)++;
    }
    return SUCCESS;
}

static int check_history_ll(int fd, shell_parameters_t *shell, int *line_nb)
{
    char *line = NULL;
    char *cmd = build_cmd_string(shell);
    char *history_path = get_history_path(shell);
    FILE *file = fopen(history_path, "r");

    free(history_path);
    if (!file || !cmd) {
        if (file)
            fclose(file);
        (void)fd;
        free(cmd);
        return EXIT_FAIL;
    }
    read_history_file(file, &line, line_nb);
    fclose(file);
    free(cmd);
    free(line);
    return SUCCESS;
}

void push_to_history(shell_parameters_t *shell)
{
    int fd;
    struct stat s;
    int history_exists = 1;
    int line_nb = 1;
    char *history_path = get_history_path(shell);

    if (stat(history_path, &s) == -1)
        history_exists = 0;
    fd = open(history_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    free(history_path);
    if (history_exists && check_history_ll(fd, shell, &line_nb) != 0)
        return;
    write_full_cmd(shell, fd, line_nb);
    close(fd);
}
