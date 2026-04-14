/*
** EPITECH PROJECT, 2025
** my_strcpy
** File description:
** Copies a string to another one.
*/
#include "./../../includes/global.h"

char *my_str_remove_char(char const *src, char to_remove)
{
    int len = my_strlen(src);
    char *new_str = malloc((len + 1 - my_str_count_char(src, to_remove))
        * sizeof(char));
    int i = 0;
    int j = 0;

    if (!new_str)
        return NULL;
    for (; src[i] != '\0'; i++) {
        if (src[i] != to_remove) {
            new_str[j] = src[i];
            j++;
        }
    }
    new_str[j] = '\0';
    return new_str;
}
