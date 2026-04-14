/*
** EPITECH PROJECT, 2025
** str_to_word_array.c
** File description:
** Transform a char * into a word char **.
*/
#include "../includes/global.h"

static int operator_assert(int e, int i, char **operators, char *str)
{
    if (my_strlen(operators[e]) == 1) {
        if (str[i] == operators[e][0])
            return 1;
    }
    if (my_strlen(operators[e]) == 2 && str[i + 1]) {
        if (str[i] == operators[e][0] && str[i + 1] == operators[e][1])
            return 2;
    }
    return SUCCESS;
}

static int operator_found(char *str, int i)
{
    char *operators[11] = {"<<", ">>", "&&", "||", "|", ";", "<",
        ">", "(", ")", NULL};
    int val = 0;

    for (int e = 0; operators[e] != NULL; e++) {
        val = operator_assert(e, i, operators, str);
        if (val != 0)
            return val;
    }
    return SUCCESS;
}

int detect_operators(char *str, int *i)
{
    int val = operator_found(str, (*i));

    if (val == 0)
        return 0;
    return val;
}
