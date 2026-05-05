/*
** EPITECH PROJECT, 2026
** split_words.c
** File description:
** Splits a command line into an array of words
*/
#include <stdlib.h>
#include "global.h"
#include "lexer.h"
#include "shell.h"

static void free_word_array(char **res)
{
    if (!res)
        return;
    for (int i = 0; res[i]; i++)
        free(res[i]);
    free(res);
}

char **lex_split_words(shell_parameters_t *shell)
{
    int count = 0;
    char **result = NULL;

    if (shell == NULL || shell->line == NULL)
        return NULL;
    count = count_words(shell->line);
    if (count == 0)
        return NULL;
    result = calloc(count + 1, sizeof(char *));
    if (result == NULL)
        return NULL;
    if (build_word_array(shell->line, result) == EXIT_FAIL) {
        free_word_array(result);
        return NULL;
    }
    return result;
}
