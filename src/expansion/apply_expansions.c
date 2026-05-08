/*
** EPITECH PROJECT, 2026
** apply_expansions.c
** File description:
** Apply expansions to the command arguments before execution
*/
#include "expansion.h"
#include "shell.h"

void apply_expansions(shell_parameters_t *shell)
{
    if (!shell || !shell->command)
        return;
    expand_globbings(shell, &shell->command);
    expand_aliases(shell, &shell->command);
}
