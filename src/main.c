/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** This file contains all my main functions.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "env.h"
#include "execution.h"
#include "global.h"
#include "lexer.h"
#include "shell.h"
#include "utils.h"

int cleanup_launcher(shell_parameters_t *shell)
{
    shell_clean(shell);
    return SUCCESS;
}

static void check_status(shell_parameters_t *shell)
{
    if (shell->last_exit_code != 0)
        printf(" \033[1;31m$\033[0m> ");
    else
        printf(" \033[1;32m$\033[0m> ");
}

static void free_command(char **cmd)
{
    if (!cmd)
        return;
    for (int i = 0; cmd[i]; i++)
        free(cmd[i]);
    free(cmd);
}

static void reset_input_buffer(shell_parameters_t *shell)
{
    free(shell->line);
    shell->line = NULL;
    shell->line_lenght = 0;
}

static int process_input(shell_parameters_t *shell)
{
    shell->nread = getline(&shell->line, &shell->line_lenght, stdin);
    if (shell->nread == -1)
        return EXIT_FAIL;
    if (shell->nread > 0 && shell->line[shell->nread - 1] == '\n')
        shell->line[shell->nread - 1] = '\0';
    free_command(shell->command);
    shell->command = lex_split_words(shell);
    if (!shell->command) {
        reset_input_buffer(shell);
        return SUCCESS;
    }
    handle_cmd_parsing(shell);
    reset_input_buffer(shell);
    safe_free((void **)&shell->command_real_path);
    free_command(shell->command);
    shell->command = NULL;
    return SUCCESS;
}

int main_loop(shell_parameters_t *shell)
{
    if (!shell)
        return EXIT_FAIL;
    shell->line = NULL;
    shell->line_lenght = 0;
    while (shell->status == RUNNING) {
        if (isatty(STDIN_FILENO)) {
            getcwd(shell->pwd, sizeof(shell->pwd));
            printf("%s", shell->pwd);
            check_status(shell);
        }
        if (process_input(shell) == EXIT_FAIL)
            break;
    }
    free(shell->line);
    shell->line = NULL;
    if (shell->command)
        free_command(shell->command);
    shell->command = NULL;
    return cleanup_launcher(shell);
}

int main(int ac, char **av, char **env)
{
    shell_parameters_t shell =
    {RUNNING, NULL, {'\0'}, NULL, 0, 0, 0, -1, NULL, NULL, NULL, NULL};

    if (ac > 2)
        return EXIT_FAIL;
    if (ac == 2 && freopen(av[1], "r", stdin) == NULL)
        return EXIT_FAIL;
    shell.env = duplicate_env(env);
    env_extract_paths(&shell);
    main_loop(&shell);
    return SUCCESS;
}
