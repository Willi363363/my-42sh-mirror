/*
** EPITECH PROJECT, 2026
** split_words.c
** File description:
** Splits a command line into an array of words
*/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "lexer.h"
#include "shell.h"
#include "utils.h"

static bool handle_quotes(char c, char *depth)
{
    if (c != '\'' && c != '"')
        return false;
    if (*depth == c) {
        *depth = 0;
        return true;
    }
    if (*depth == 0) {
        *depth = c;
        return true;
    }
    return false;
}

static void fill_word(char *line, size_t *cursor, char *word)
{
    size_t word_len = 0;
    char depth = 0;

    for (; line[*cursor]; (*cursor)++) {
        if (line[*cursor] == ' ' && depth == 0)
            break;
        if (handle_quotes(line[*cursor], &depth))
            continue;
        word[word_len] = line[*cursor];
        word_len++;
    }
    word[word_len] = '\0';
}

static int extract_word(char *line, size_t *cursor, char ***words)
{
    char word[MAX_ARG_LEN] = {0};

    fill_word(line, cursor, word);
    if (word_array_push(words, word) == EXIT_FAIL)
        return EXIT_FAIL;
    return SUCCESS;
}

char **lex_split_words(shell_parameters_t *shell)
{
    char **words = NULL;
    size_t cursor = 0;

    while (shell->line[cursor]) {
        while (shell->line[cursor] == ' ')
            cursor++;
        if (!shell->line[cursor])
            break;
        if (extract_word(shell->line, &cursor, &words) == EXIT_FAIL) {
            word_array_destroy(&words);
            return NULL;
        }
    }
    return words;
}
