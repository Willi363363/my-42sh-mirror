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
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
                (str[i] >= 'A' && str[i] <= 'Z') ||
                (str[i] >= '0' && str[i] <= '9')))
            return EXIT_FAIL;
    }
    return SUCCESS;
}
