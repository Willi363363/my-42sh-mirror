/*
** EPITECH PROJECT, 2025
** lex_operators.c
** File description:
** Lexical analysis of operators in the input string.
*/
#include <string.h>
#include "global.h"

static int operator_assert(int e, int i, char **operators, char *str)
{
    if (strlen(operators[e]) == 1) {
        if (str[i] == operators[e][0])
            return EXIT_FAIL;
    }
    if (strlen(operators[e]) == 2 && str[i + 1]) {
        if (str[i] == operators[e][0] && str[i + 1] == operators[e][1])
            return 2;
    }
    return SUCCESS;
}

static int operator_found(char *str, int i)
{
    char *operators[11] =
    {"<<", ">>", "&&", "||", "|", ";", "<", ">", "(", ")", NULL};
    int val = 0;

    for (int e = 0; operators[e] != NULL; e++) {
        val = operator_assert(e, i, operators, str);
        if (val != 0)
            return val;
    }
    return SUCCESS;
}

int lex_operators(char *str, int *i)
{
    int val = operator_found(str, (*i));

    if (val == 0)
        return 0;
    return val;
}
