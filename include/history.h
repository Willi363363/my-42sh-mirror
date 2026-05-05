/*
** EPITECH PROJECT, 2026
** history.h
** File description:
** History header file
*/
#ifndef HISTORY_H
    #define HISTORY_H
    #define HISTORY_FILE_NAME ".cod_history"
    #include "shell.h"

char *get_history_path(shell_parameters_t *shell);
void push_to_history(shell_parameters_t *shell);

#endif /* !HISTORY_H */
