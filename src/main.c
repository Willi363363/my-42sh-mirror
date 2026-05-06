/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** This file contains all my main functions.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "global.h"
#include "lexer.h"
#include "parsing.h"
#include "shell.h"
#include "utils.h"

static void print_prompt_line(shell_parameters_t *shell)
{
    char *color = shell->last_exit_code != 0 ? RED : GREEN;

    if (isatty(STDIN_FILENO)) {
        getcwd(shell->pwd, sizeof(shell->pwd));
        printf("%s %s$%s> ", shell->pwd, color, RESET);
    }
}

static void free_command(shell_parameters_t *shell)
{
    if (!shell->command)
        return;
    for (int i = 0; shell->command[i]; i++)
        free(shell->command[i]);
    free(shell->command);
    shell->command = NULL;
}

static int reset_input_buffer(shell_parameters_t *shell, char *line_backup)
{
    if (line_backup)
        free(line_backup);
    else if (shell->line)
        free(shell->line);
    shell->line = NULL;
    shell->line_lenght = 0;
    return SUCCESS;
}

static int process_input(shell_parameters_t *shell)
{
    char *line_backup = NULL;

    free_command(shell);
    shell->nread = getline(&shell->line, &shell->line_lenght, stdin);
    if (shell->nread == -1) {
        reset_input_buffer(shell, line_backup);
        return EXIT_FAIL;
    }
    if (shell->nread > 0 && shell->line[shell->nread - 1] == '\n')
        shell->line[shell->nread - 1] = '\0';
    line_backup = shell->line;
    shell->command = lex_split_words(shell);
    if (!shell->command)
        return reset_input_buffer(shell, line_backup);
    handle_cmd_parsing(shell);
    reset_input_buffer(shell, line_backup);
    safe_free((void **)&shell->command_real_path);
    free_command(shell);
    return SUCCESS;
}

int main_loop(shell_parameters_t *shell)
{
    if (!shell)
        return EXIT_FAIL;
    while (shell->status == RUNNING) {
        print_prompt_line(shell);
        if (process_input(shell) == EXIT_FAIL)
            break;
    }
    shell_clean(shell);
    return SUCCESS;
}

int main(int ac, char **av, char **env)
{
    shell_parameters_t shell = {0};

    if (ac > 2)
        return EXIT_FAIL;
    if (ac == 2 && freopen(av[1], "r", stdin) == NULL)
        return EXIT_FAIL;
    shell_init(&shell, env);
    main_loop(&shell);
    if (isatty(STDIN_FILENO))
        return SUCCESS;
    return shell.last_exit_code;
}
