/*
** EPITECH PROJECT, 2025
** launch.c
** File description:
** This file launch the cod editor.
*/
#include "global.h"

int cod(shell_parameters_t *shell)
{
    file_infos_t file_infos;
    struct stat file_stat;
    char *custom_file_name;
    int ac = my_tablen(shell->command);

    if (ac != 2)
        return display_help_message(EXIT_FAIL);
    if (strcmp(shell->command[1], "--help") == 0
        || strcmp(shell->command[1], "--h") == 0)
            return display_help_message(SUCCESS);
    if (strcmp(shell->command[1], "--version") == 0
        || strcmp(shell->command[1], "--v") == 0)
        return display_version_message(SUCCESS);
    return SUCCESS;
}
