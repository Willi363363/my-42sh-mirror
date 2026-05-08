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
#include <stdlib.h>
#include <string.h>
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
        my_putstr_error((char *)path);
        my_putstr_error(": No such file or directory.\n");
        shell->last_exit_code = EXIT_FAIL;
        return false;
    }
    if (!S_ISDIR(s.st_mode)) {
        my_putstr_error((char *)path);
        my_putstr_error(": Not a directory.\n");
        shell->last_exit_code = EXIT_FAIL;
        return false;
    }
    return true;
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
    char *safe = strdup(path);
    int ret = COMMAND_ERROR;

    if (!safe)
        return COMMAND_ERROR;
    if (!is_valid_directory(safe, shell) || update_oldpwd(shell) == EXIT_FAIL) {
        free(safe);
        return COMMAND_ERROR;
    }
    if (chdir(safe) == -1) {
        my_putstr_error(safe);
        my_putstr_error(": Permission denied.\n");
        shell->last_exit_code = EXIT_FAIL;
    } else if (update_pwd(shell) != EXIT_FAIL) {
        shell->last_exit_code = SUCCESS;
        ret = COMMAND_FOUND;
    }
    free(safe);
    return ret;
}
