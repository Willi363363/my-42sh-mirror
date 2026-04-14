/*
** EPITECH PROJECT, 2025
** my_strncmp
** File description:
** Copies a string to another one.
*/
#include "./../../includes/global.h"

int my_strncmp(char const *s1, char const *s2, int len)
{
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        if (s1[i] == '\0')
            return 0;
    }
    return 0;
}
