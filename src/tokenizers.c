/*
** EPITECH PROJECT, 2025
** tokenizers_parse.c
** File description:
** This file contains all my functions that crops.
*/
#include "../includes/global.h"

int my_strcmp_skip(char const *skip_here, char const *s2, int chars_to_skip)
{
    for (int i = 0; skip_here[i + chars_to_skip] != '\0' &&
        s2[i] != '\0'; i++) {
        if (skip_here[i + chars_to_skip] != s2[i]) {
            return skip_here[i + chars_to_skip] - s2[i];
        }
    }
    return skip_here[chars_to_skip] - s2[0];
}

char *crop_str_skip(char *str, int chars_to_skip)
{
    char *res = malloc((my_strlen(str) - chars_to_skip + 1));
    int i = 0;

    for (; str[i + chars_to_skip] != '\0'; i++)
        res[i] = str[i + chars_to_skip];
    res[i] = '\0';
    return res;
}
