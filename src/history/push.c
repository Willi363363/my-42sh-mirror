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

static int ll_full_clean(char *old, char *cmd, char *line)
{
    if (old && strcmp(old, cmd) == 0) {
        free(line);
        free(old);
        free(cmd);
        return 1;
    }
    free(line);
    free(old);
    free(cmd);
    return SUCCESS;
}

static int check_history_ll(int fd, shell_parameters_t *shell, int *line_nb)
{
    char *line = NULL;
    size_t line_lenght = 0;
    char *old = NULL;
    char *cmd = build_cmd_string(shell);
    FILE *file = fopen("history", "r");

    if (!file || !cmd) {
        free(cmd);
        return EXIT_FAIL;
    }
    while (getline(&line, &line_lenght, file) != -1) {
        if (old)
            free(old);
        old = my_strdup(line);
        (*line_nb)++;
    }
    fclose(file);
    if (ll_full_clean(old, cmd, line))
        return 1;
    return SUCCESS;
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
