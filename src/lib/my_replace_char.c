/*
** EPITECH PROJECT, 2025
** my_put_nbr.c
** File description:
** This script displays the number given as a parameter.
*/
#include "./../../includes/global.h"

int my_replace_char(char *str, char to_replace, char replacer)
{
    int not_found = -1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_replace) {
            str[i] = replacer;
            not_found = 0;
        }
    }
    return not_found;
}
