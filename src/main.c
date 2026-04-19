/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** This file contains all my main functions.
*/
#include "../includes/global.h"

static void command_not_found(shell_parameters_t *shell, char *command)
{
    my_putstr_error(command);
    my_putstr_error(": Command not found.\n");
    shell->last_exit_code = EXIT_FAIL;
}

int commands_launcher(shell_parameters_t *shell)
{
    int found = 0;

    found = misc_cmds_assert(shell->line, shell);
    if (found == 0 && found != COMMAND_ERROR)
        found = assert_sys_cmd(shell);
    if (found == 0 && found != COMMAND_ERROR)
        found = env_cmds_assert(shell->line, shell);
    if (found == 0 && found != COMMAND_ERROR)
        found = dir_cmds_assert(shell->line, shell);
    if (found == 0 && found != COMMAND_ERROR)
        found = own_cmds_assert(shell);
    if (found == COMMAND_FOUND || found == COMMAND_ERROR)
        return SUCCESS;
    command_not_found(shell, shell->command[0]);
    return EXIT_FAIL;
}

int cleanup_launcher(shell_parameters_t *shell)
{
    clean_and_exit(shell);
    return SUCCESS;
}

static void check_status(shell_parameters_t *shell)
{
    if (shell->last_exit_code != 0)
        my_putstr(" \033[1;31m$\033[0m> ");
    else
        my_putstr(" \033[1;32m$\033[0m> ");
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

static void cleanup_parsed_command(shell_parameters_t *shell, char **parsed_cmd)
{
    my_safe_free((void **)&shell->command_real_path);
    shell->command = NULL;
    free_command(parsed_cmd);
}

static int process_input(shell_parameters_t *shell)
{
    char **parsed_cmd = NULL;

    shell->nread = getline(&shell->line, &shell->line_lenght, stdin);
    if (shell->nread == -1)
        return EXIT_FAIL;
    if (shell->nread > 0 && shell->line[shell->nread - 1] == '\n')
        shell->line[shell->nread - 1] = '\0';
    parsed_cmd = tokenize_formatter(shell);
    if (!parsed_cmd) {
        reset_input_buffer(shell);
        return SUCCESS;
    }
    free_command(shell->command);
    shell->command = parsed_cmd;
    execute_ast(shell);
    reset_input_buffer(shell);
    my_safe_free((void **)&shell->command_real_path);
    shell->command = NULL;
    free_command(parsed_cmd);
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
            my_putstr(shell->pwd);
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
    shell_parameters_t shell = {RUNNING, NULL, {'\0'}, NULL, 0, 0, 0, -1,
        NULL, NULL, NULL, NULL};

    if (ac > 2)
        return EXIT_FAIL;
    if (ac == 2 && freopen(av[1], "r", stdin) == NULL)
        return EXIT_FAIL;
    shell.env = duplicate_env(env);
    create_paths(&shell);
    main_loop(&shell);
    return SUCCESS;
}
