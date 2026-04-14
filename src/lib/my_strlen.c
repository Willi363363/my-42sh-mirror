/*
** EPITECH PROJECT, 2025
** my_strlen.c
** File description:
** This programm returns the number of chars found in a given string.
*/
#include "../../includes/global.h"

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return 0;
    for (i = 0; str[i] != '\0'; i++){
    }
    return i;
}
