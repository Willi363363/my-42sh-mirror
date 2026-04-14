/*
** EPITECH PROJECT, 2025
** dir_cmds.c
** File description:
** This file contains all my directories commands functions.
*/
#include "../../../includes/global.h"

static int change_wd(shell_parameters_t *shell)
{
    char *new_wd = NULL;

    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], "PWD=", 4) == 0) {
            getcwd(shell->pwd, sizeof(shell->pwd));
            my_safe_free((void **)&shell->env[i]);
            new_wd = malloc((5 + my_strlen(shell->pwd)) * sizeof(char));
            my_strcpy(new_wd, "PWD=");
            my_strcat(new_wd, shell->pwd);
            shell->env[i] = my_strdup(new_wd);
            free(new_wd);
            return SUCCESS;
        }
    }
    return EXIT_FAIL;
}

static int test_if_path_exists(char *path, shell_parameters_t *shell)
{
    struct stat s;

    if (stat(path, &s) == -1) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error("cd : path not found\n");
        return EXIT_FAIL;
    }
    if (!(S_ISDIR(s.st_mode))) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error(path);
        my_putstr_error(": Not a directory.\n");
        return EXIT_FAIL;
    }
    if (opendir(path) == NULL) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error("cd : path not found\n");
        return EXIT_FAIL;
    }
    return SUCCESS;
}

static int change_directory(shell_parameters_t *shell)
{
    backup_old_pwd(shell);
    if (my_tablen(shell->command) != 2) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error("cd : too many arguments\n");
        return COMMAND_ERROR;
    }
    if (test_if_path_exists(shell->command[1], shell) == EXIT_FAIL)
        return COMMAND_ERROR;
    chdir(shell->command[1]);
    if (change_wd(shell) == EXIT_FAIL) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error("cd : failed to change the env var\n");
        return COMMAND_ERROR;
    }
    return COMMAND_FOUND;
}

int get_home(shell_parameters_t *shell)
{
    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], "HOME=", 5) == 0) {
            shell->home = my_strdup_skip_chars(shell->env[i], 5);
            return SUCCESS;
        }
    }
    return EXIT_FAIL;
}

static int change_directory_root(shell_parameters_t *shell)
{
    backup_old_pwd(shell);
    if (get_home(shell) == EXIT_FAIL) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error("cd : failed to find home path\n");
        return COMMAND_ERROR;
    }
    chdir(shell->home);
    return COMMAND_FOUND;
}

static int go_to_old_dir(shell_parameters_t *shell)
{
    char *old_wd = NULL;
    char backup_current_wd[MAX_PATH_LEN] = {'\0'};

    getcwd(backup_current_wd, sizeof(backup_current_wd));
    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], "OLDPWD=", 7) == 0) {
            old_wd = my_strdup_skip_chars(shell->env[i], 7);
        }
    }
    if (!old_wd) {
        shell->last_exit_code = EXIT_FAIL;
        my_putstr_error("cd : failed to find oldpwd path\n");
        return COMMAND_ERROR;
    }
    chdir(old_wd);
    free(old_wd);
    backup_old_pwd_with(shell, backup_current_wd);
    return COMMAND_FOUND;
}

int dir_cmds_assert(char *line, shell_parameters_t *shell)
{
    if (shell->command_found == SUCCESS)
        return SUCCESS;
    if (my_strncmp(line, "cd", 2) == 0 &&
        (line[2] == '\n' || line[2] == '\0'))
        return change_directory_root(shell);
    if (my_strncmp(line, "cd ~", 4) == 0 &&
        (line[4] == '\n' || line[4] == '\0'))
        return change_directory_root(shell);
    if (my_strncmp(line, "cd -", 4) == 0 &&
        (line[4] == '\n' || line[4] == '\0'))
        return go_to_old_dir(shell);
    if (my_strncmp(line, "cd", 2) == 0)
        return change_directory(shell);
    return SUCCESS;
}
