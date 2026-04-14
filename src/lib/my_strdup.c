/*
** EPITECH PROJECT, 2025
** my_strcpy
** File description:
** Copies a string to another one.
*/
#include "./../../includes/global.h"

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *new_str = malloc((len + 1) * sizeof(char));

    if (!new_str)
        return NULL;
    my_strcpy(new_str, src);
    return new_str;
}
