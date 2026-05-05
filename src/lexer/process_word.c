/*
** EPITECH PROJECT, 2026
** process_word.c
** File description:
** This file contains the function to process a word in the lexer.
*/
#include "lexer.h"

static void detect_if_quoted(char *str, int *i, int *wsize)
{
    while (str[*i] != '"' && str[*i] != '\0') {
        (*wsize)++;
        (*i)++;
    }
    if (str[*i] == '"')
        (*i)++;
}

static void detect_normal(char *str, int *i, int *wsize)
{
    int res = lex_operators(str, i);

    if (res != 0) {
        *wsize = res;
        return;
    }
    while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '\t'
        && lex_operators(str, i) == 0) {
        (*wsize)++;
        (*i)++;
    }
}

int process_word(char *str, int i, int *start, int *wsize)
{
    int op_res = lex_operators(str, &i);

    if (op_res != 0) {
        *start = i;
        *wsize = op_res;
        return i + op_res;
    }
    if (str[i] == '"') {
        *start = i + 1;
        i++;
        detect_if_quoted(str, &i, wsize);
    } else {
        *start = i;
        detect_normal(str, &i, wsize);
    }
    return i;
}
