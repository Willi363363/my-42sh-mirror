/*
** EPITECH PROJECT, 2025
** own_files_cmds.c
** File description:
** This file contains all the user's commands functions.
*/
#include "../../includes/global.h"

static void binary_file_error(shell_parameters_t *shell)
{
    my_putstr_error(shell->command[0]);
    my_putstr_error(": Exec format error. Binary file not executable.\n");
}

static int execute_own_file(shell_parameters_t *shell)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == -1)
        return EXIT_FAIL;
    if (pid == 0) {
        execve(shell->command[0], shell->command, shell->env);
        if (errno == ENOEXEC)
            binary_file_error(shell);
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

static int is_folder_maybe(int fd)
{
    struct stat s;

    if (fstat(fd, &s) == -1)
        return EXIT_FAIL;
    if (S_ISDIR(s.st_mode))
        return EXIT_FAIL;
    return SUCCESS;
}

int close_and_return_code(int fd, int code)
{
    close(fd);
    return code;
}

static int error_folder(shell_parameters_t *shell, int fd)
{
    close(fd);
    my_putstr_error(shell->command[0]);
    my_putstr_error(": Permission denied.\n");
    shell->last_exit_code = EXIT_FAIL;
    return COMMAND_FOUND;
}

int own_cmds_assert(shell_parameters_t *shell)
{
    int fd = 0;

    if (shell->command == NULL || shell->command[0] == NULL)
        return SUCCESS;
    fd = open(shell->command[0], O_RDONLY);
    if (fd == -1)
        return 0;
    if (is_folder_maybe(fd) == EXIT_FAIL)
        return error_folder(shell, fd);
    if (access(shell->command[0], X_OK) == SUCCESS) {
        execute_own_file(shell);
    } else {
        my_putstr_error(shell->command[0]);
        my_putstr_error(": you do not have the rights to execute this file.\n");
        shell->last_exit_code = EXIT_FAIL;
        return close_and_return_code(fd, COMMAND_FOUND);
    }
    return close_and_return_code(fd, COMMAND_FOUND);
}
