/*
** EPITECH PROJECT, 2025
** my_strcpy_limit.c
** File description:
** Copies a string to another one.
*/
#include "./../../includes/global.h"

int my_strcpy_limit(char *dest, char const *src, int max)
{
    for (int i = 0; i < max && src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[my_strlen(src)] = '\0';
    return SUCCESS;
}
