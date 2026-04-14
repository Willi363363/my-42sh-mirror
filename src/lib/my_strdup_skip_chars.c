/*
** EPITECH PROJECT, 2025
** my_strcpy
** File description:
** Copies a string to another one.
*/
#include "./../../includes/global.h"

char *my_strdup_skip_chars(char const *src, int to_skip)
{
    int len = my_strlen(src) - to_skip;
    char *new_str = malloc((len + 1) * sizeof(char));

    if (!new_str)
        return NULL;
    for (int i = 0; i < len; i++)
        new_str[i] = src[i + to_skip];
    new_str[len] = '\0';
    return new_str;
}
