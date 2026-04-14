/*
** EPITECH PROJECT, 2025
** my_strcmp
** File description:
** Copies a string to another one.
*/
#include "./../../includes/global.h"

int my_strcmp(char const *s1, char const *s2)
{
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
    }
    return s1[0] - s2[0];
}
