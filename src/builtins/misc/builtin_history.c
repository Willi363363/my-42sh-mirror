/*
** EPITECH PROJECT, 2025
** builtin_history.c
** File description:
** Misc history builtin
*/
#include <stdio.h>
#include "global.h"
#include "shell.h"
#include "utils.h"
#include "builtins/misc.h"

int builtin_history(shell_parameters_t *shell)
{
    FILE *h = fopen("history", "r");
    char content[1024];

    if (!h) {
        my_putstr_error("History file not found.\n");
        shell->last_exit_code = EXIT_FAIL;
        return COMMAND_ERROR;
    }
    while (fgets(content, 1024, h) != NULL)
        fprintf(stdout, "%s", content);
    fclose(h);
    shell->last_exit_code = SUCCESS;
    return COMMAND_FOUND;
}
