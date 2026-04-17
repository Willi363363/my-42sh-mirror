/*
** EPITECH PROJECT, 2025
** history.c
** File description:
** This file contains the history builtin.
*/
#include "global.h"

int display_history(shell_parameters_t *shell)
{
    FILE *h = fopen("history", "r");
    char content[1024];

    if (!h) {
        my_putstr_error("History file not found.\n");
        shell->last_exit_code = EXIT_FAIL;
        return COMMAND_ERROR;
    }
    while (fgets(content, 1024, h) != NULL)
        fprintf(stdout, "%s", content);
    fclose(h);
    shell->last_exit_code = SUCCESS;
    return COMMAND_FOUND;
}

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

static int ll_full_clean(char *old, char *cmd)
{
    if (old && cmd && strcmp(old, cmd) == 0)
        return 1;
    return SUCCESS;
}

static int read_history_file(FILE *file, char **old, char **line, int *line_nb)
{
    size_t len = 0;

    while (getline(line, &len, file) != -1) {
        free(*old);
        *old = my_strdup(*line);
        (*line_nb)++;
    }
    return SUCCESS;
}

static int check_history_ll(int fd, shell_parameters_t *shell, int *line_nb)
{
    char *line = NULL;
    char *old = NULL;
    char *cmd = build_cmd_string(shell);
    FILE *file = fopen("history", "r");
    int ret = 0;

    if (!file || !cmd) {
        if (file)
            fclose(file);
        free(cmd);
        return EXIT_FAIL;
    }
    read_history_file(file, &old, &line, line_nb);
    fclose(file);
    ret = ll_full_clean(old, cmd);
    free(old);
    free(cmd);
    free(line);
    return (ret == 1) ? 1 : SUCCESS;
}

void push_to_history(shell_parameters_t *shell)
{
    int fd;
    struct stat s;
    int history_exists = 1;
    int line_nb = 1;

    if (stat("history", &s) == -1)
        history_exists = 0;
    fd = open("history", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (history_exists &&
        check_history_ll(fd, shell, &line_nb) != 0)
        return;
    write_full_cmd(shell, fd, line_nb);
    close(fd);
}
