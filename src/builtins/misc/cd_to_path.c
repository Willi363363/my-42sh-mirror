/*
** EPITECH PROJECT, 2026
** cd_to_path.c
** File description:
** Change the current working directory to a specified path
*/
#include <dirent.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "builtins/misc.h"
#include "env.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static bool is_valid_directory(const char *path, shell_parameters_t *shell)
{
    struct stat s;

    if (stat(path, &s) == -1) {
        perror("cd");
        shell->last_exit_code = EXIT_FAIL;
        return 0;
    }
    if (!S_ISDIR(s.st_mode)) {
        my_putstr_error("cd: not a directory\n");
        shell->last_exit_code = EXIT_FAIL;
        return 0;
    }
    return 1;
}

static int update_pwd(shell_parameters_t *shell)
{
    char cwd[MAX_PATH_LEN];

    if (!getcwd(cwd, sizeof(cwd)))
        return EXIT_FAIL;
    return my_setenv(shell, "PWD", cwd);
}

static int update_oldpwd(shell_parameters_t *shell)
{
    char cwd[MAX_PATH_LEN];

    if (!getcwd(cwd, sizeof(cwd)))
        return EXIT_FAIL;
    return my_setenv(shell, "OLDPWD", cwd);
}

int cd_to_path(shell_parameters_t *shell, const char *path)
{
    if (!is_valid_directory(path, shell))
        return COMMAND_ERROR;
    if (update_oldpwd(shell) == EXIT_FAIL)
        return COMMAND_ERROR;
    if (chdir(path) == -1) {
        perror("cd");
        shell->last_exit_code = EXIT_FAIL;
        return COMMAND_ERROR;
    }
    return update_pwd(shell);
}
