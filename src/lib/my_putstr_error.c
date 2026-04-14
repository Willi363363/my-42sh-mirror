/*
** EPITECH PROJECT, 2025
** my_putstr.c
** File description:
** Displays
*/
#include "./../../includes/global.h"

int my_putstr_error(char const *str)
{
    int ret = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        ret = write(2, &str[i], 1);
        if (ret == -1)
            return 84;
    }
    return 0;
}
