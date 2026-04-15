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

int cod(shell_parameters_t *shell)
{
    file_infos_t file_infos;
    struct stat file_stat;
    char *custom_file_name;
    int ac = my_tablen(shell->command);

    if (ac != 2) {
        shell->last_exit_code = EXIT_FAIL;
        return editor_help(COMMAND_ERROR);
    }
    if (strncmp(shell->command[1], "--", 2) == 0)
        return option_check(shell);
    return COMMAND_FOUND;
}
