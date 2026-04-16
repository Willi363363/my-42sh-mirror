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

int main_loop(shell_parameters_t *shell)
{
    shell->line = NULL;
    shell->line_lenght = 0;
    while (shell->status == RUNNING) {
        getcwd(shell->pwd, sizeof(shell->pwd));
        my_putstr(shell->pwd);
        check_status(shell);
        shell->nread = getline(&shell->line, &shell->line_lenght, stdin);
        if (shell->nread == -1)
            break;
        if (shell->nread > 0 && shell->line[shell->nread - 1] == '\n')
            shell->line[shell->nread - 1] = '\0';
        shell->command = tokenize_formatter(shell);
        if (shell->command != NULL) {
            execute_ast(shell);
            push_to_history(shell);
        }
        clean_every_iteration(shell);
    }
    return cleanup_launcher(shell);
}

int main(int ac, char **av, char **env)
{
    shell_parameters_t shell = {RUNNING, NULL, {'\0'}, NULL, 0, 0, 0, -1,
        NULL, NULL, NULL, NULL};

    shell.env = duplicate_env(env);
    create_paths(&shell);
    main_loop(&shell);
    return SUCCESS;
}
