/*
** EPITECH PROJECT, 2025
** system_cmds.c
** File description:
** This file contains all the user's commands functions.
*/
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "execution.h"
#include "global.h"
#include "shell.h"

static int execute_sys_command(shell_parameters_t *shell)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == -1)
        return EXIT_FAIL;
    if (pid == 0) {
        execve(shell->command_real_path, shell->command, shell->env);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            shell->last_exit_code = WEXITSTATUS(status);
        else
            shell->last_exit_code = handle_signal(status);
    }
    return SUCCESS;
}

static int try_path(shell_parameters_t *shell, int i)
{
    char *test_path = NULL;

    test_path = malloc(strlen(shell->paths[i]) + 2 + strlen(shell->command[0]));
    test_path[0] = '\0';
    strcat(test_path, shell->paths[i]);
    strcat(test_path, "/");
    strcat(test_path, shell->command[0]);
    if (access(test_path, X_OK) == 0) {
        shell->command_real_path = strdup(test_path);
        free(test_path);
        return 1;
    }
    free(test_path);
    return SUCCESS;
}

static int find_command_path(shell_parameters_t *shell)
{
    if (shell->paths == NULL)
        return SUCCESS;
    for (int i = 0; shell->paths[i] != NULL; i++) {
        if (try_path(shell, i) == 1)
            return 1;
    }
    return SUCCESS;
}

int exec_system_cmd(shell_parameters_t *shell)
{
    if (shell->command == NULL || shell->command[0] == NULL)
        return SUCCESS;
    if (find_command_path(shell) == 1) {
        execute_sys_command(shell);
        return COMMAND_FOUND;
    }
    return SUCCESS;
}
