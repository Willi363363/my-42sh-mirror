/*
** EPITECH PROJECT, 2025
** launch.c
** File description:
** This file launch the cod editor.
*/
#include "global.h"

static int option_check(shell_parameters_t *shell)
{
    if (strcmp(shell->command[1], "--help") == 0
        || strcmp(shell->command[1], "--h") == 0) {
        shell->last_exit_code = SUCCESS;
        return editor_help(COMMAND_FOUND);
    }
    if (strcmp(shell->command[1], "--version") == 0
        || strcmp(shell->command[1], "--v") == 0) {
        shell->last_exit_code = SUCCESS;
        return editor_version(COMMAND_FOUND);
    }
    shell->last_exit_code = EXIT_FAIL;
    printf("%s: option not found. Try --h or --v.\n", shell->command[1]);
    return COMMAND_ERROR;
}

static int fill_infos(file_infos_t *file_infos,
    struct stat *file_stat, shell_parameters_t *shell)
{
    file_infos->filepath =
        malloc((strlen(shell->command[1]) + 1) * sizeof(char));
    if (!file_infos->filepath)
        return EXIT_FAIL;
    file_infos->file_stat = file_stat;
    file_infos->fd = -1;
    file_infos->filecontent = NULL;
    strcpy(file_infos->filepath, shell->command[1]);
    return SUCCESS;
}

static int create_f(file_infos_t *file_infos, shell_parameters_t *shell)
{
    if (check_if_file_is_here(file_infos) == EXIT_FAIL) {
        if (create_new_file_ask() == SUCCESS) {
            create_new_file(shell->command[1]);
            fill_new_file_infos(shell->command[1], file_infos);
            file_infos->fd = open(shell->command[1], O_RDONLY);
            stat(shell->command[1], file_infos->file_stat);
        }
        free(file_infos->filepath);
        return COMMAND_FOUND;
    }
    return SUCCESS;
}

static int launch_assert(file_infos_t *file_infos, shell_parameters_t *shell)
{
    if (read_the_file(file_infos) == EXIT_FAIL) {
        free_it(file_infos);
        shell->last_exit_code = EXIT_FAIL;
        return COMMAND_ERROR;
    }
    if (window_loop(file_infos) == EXIT_FAIL) {
        free_it(file_infos);
        return COMMAND_ERROR;
    }
    return SUCCESS;
}

int cod(shell_parameters_t *shell)
{
    file_infos_t file_infos;
    struct stat file_stat;
    int ac = my_tablen(shell->command);

    if (ac != 2) {
        shell->last_exit_code = EXIT_FAIL;
        return editor_help(COMMAND_ERROR);
    }
    if (strncmp(shell->command[1], "--", 2) == 0)
        return option_check(shell);
    if (fill_infos(&file_infos, &file_stat, shell) == EXIT_FAIL)
        return COMMAND_ERROR;
    if (create_f(&file_infos, shell) == COMMAND_FOUND)
        return COMMAND_FOUND;
    if (launch_assert(&file_infos, shell) == COMMAND_ERROR)
        return COMMAND_ERROR;
    free_it(&file_infos);
    shell->last_exit_code = SUCCESS;
    return COMMAND_FOUND;
}
