/*
** EPITECH PROJECT, 2025
** system_cmds.c
** File description:
** This file contains all the user's commands functions.
*/
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "env.h"
#include "execution.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static int execute_sys_command(shell_parameters_t *shell)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == -1)
        return EXIT_FAIL;
    if (pid == 0) {
        execve(shell->command_real_path, shell->command, shell->env);
        exit(84);
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            shell->last_exit_code = WEXITSTATUS(status);
        else
            shell->last_exit_code = handle_signal(status);
    }
    return SUCCESS;
}

static bool is_target_path(shell_parameters_t *shell, char *path)
{
    char *test_path = malloc(strlen(path) + 2 + strlen(shell->command[0]));
    int fd = -1;

    test_path[0] = '\0';
    strcat(test_path, path);
    strcat(test_path, "/");
    strcat(test_path, shell->command[0]);
    fd = open(test_path, O_RDONLY);
    if (fd != -1) {
        close(fd);
        shell->command_real_path = strdup(test_path);
        free(test_path);
        return true;
    }
    free(test_path);
    return false;
}

static bool find_command_path(shell_parameters_t *shell)
{
    char **paths = env_get_paths(shell);

    if (!paths)
        return false;
    for (int i = 0; paths[i] != NULL; i++) {
        if (is_target_path(shell, paths[i])) {
            word_array_destroy(&paths);
            return true;
        }
    }
    word_array_destroy(&paths);
    return false;
}

int exec_system_cmd(shell_parameters_t *shell)
{
    if (shell->command == NULL || shell->command[0] == NULL)
        return SUCCESS;
    if (find_command_path(shell)) {
        execute_sys_command(shell);
        return COMMAND_FOUND;
    }
    return SUCCESS;
}
