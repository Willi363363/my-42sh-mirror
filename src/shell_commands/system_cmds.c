/*
** EPITECH PROJECT, 2025
** system_cmds.c
** File description:
** This file contains all the user's commands functions.
*/
#include "../../includes/global.h"

int signals_interpreter(int status)
{
    int sig = 0;

    if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        my_putstr_error(strsignal(sig));
        my_putstr_error("\n");
    }
    return 128 + sig;
}

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
            shell->last_exit_code = signals_interpreter(status);
    }
    return SUCCESS;
}

static int find_command_path(shell_parameters_t *shell)
{
    char *test_path = NULL;
    int fd = -1;

    for (int i = 0; shell->paths[i] != NULL; i++) {
        test_path = malloc(my_strlen(shell->paths[i]) + 2 +
            my_strlen(shell->command[0]));
        test_path[0] = '\0';
        my_strcat(test_path, shell->paths[i]);
        my_strcat(test_path, "/");
        my_strcat(test_path, shell->command[0]);
        fd = open(test_path, O_RDONLY);
        if (fd != -1) {
            close(fd);
            shell->command_real_path = my_strdup(test_path);
            free(test_path);
            return 1;
        }
        free(test_path);
    }
    return SUCCESS;
}

int assert_sys_cmd(shell_parameters_t *shell)
{
    if (shell->command == NULL || shell->command[0] == NULL)
        return SUCCESS;
    if (find_command_path(shell) == 1) {
        execute_sys_command(shell);
        return COMMAND_FOUND;
    }
    return SUCCESS;
}
