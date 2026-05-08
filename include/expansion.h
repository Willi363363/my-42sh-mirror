/*
** EPITECH PROJECT, 2026
** expansion.h
** File description:
** Expansion header file
*/
#ifndef EXPANSION_H
    #define EXPANSION_H
    #include "shell.h"

void apply_expansions(shell_parameters_t *shell);

void expand_globbings(shell_parameters_t *shell, char ***cmd);
void expand_aliases(shell_parameters_t *shell, char ***cmd);

#endif /* !EXPANSION_H */
