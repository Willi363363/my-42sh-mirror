/*
** EPITECH PROJECT, 2025
** is_alphanums.c
** File description:
** Check if a string is composed only of alphanumeric characters
*/
#include "global.h"
#include "utils.h"

int is_alphanums(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z'))
            continue;
        if ((str[i] >= 'A' && str[i] <= 'Z'))
            continue;
        if ((str[i] >= '0' && str[i] <= '9'))
            continue;
        if (str[i] == '_')
            continue;
        return EXIT_FAIL;
    }
    return SUCCESS;
}
