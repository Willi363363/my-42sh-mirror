/*
** EPITECH PROJECT, 2025
** my_strcpy
** File description:
** Copies a string to another one.
*/
#include "./../../includes/global.h"

int my_str_count_char(char const *src, char c)
{
    int count = 0;

    for (int i = 0; src[i] != '\0'; i++)
        if (src[i] == c)
            count++;
    return count;
}
