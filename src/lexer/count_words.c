/*
** EPITECH PROJECT, 2026
** count_words.c
** File description:
** Counts the number of words in a command line
*/
#include "lexer.h"

static int skip_quoted_word(char *str, int i)
{
    i++;
    while (str[i] != '"' && str[i] != '\0')
        i++;
    if (str[i] == '"')
        i++;
    return i;
}

static int skip_normal_word(char *str, int i)
{
    int res = lex_operators(str, &i);

    if (res != 0)
        return i + res;
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '\t'
        && lex_operators(str, &i) == 0)
        i++;
    return i;
}

static int count_recursive(char *str, int i)
{
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '\0')
        return 0;
    if (str[i] == '"')
        i = skip_quoted_word(str, i);
    else
        i = skip_normal_word(str, i);
    return 1 + count_recursive(str, i);
}

int count_words(char *str)
{
    return count_recursive(str, 0);
}
