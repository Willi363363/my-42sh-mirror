/*
** EPITECH PROJECT, 2025
** my_check_if_alphanums.c
** File description:
** Displays
*/
#include "./../../includes/global.h"

int my_check_if_alphanums(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
                (str[i] >= 'A' && str[i] <= 'Z') ||
                (str[i] >= '0' && str[i] <= '9')))
            return EXIT_FAIL;
    }
    return SUCCESS;
}
