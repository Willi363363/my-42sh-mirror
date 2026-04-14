/*
** EPITECH PROJECT, 2025
** my_strlen.c
** File description:
** This programm returns the number of chars found in a given string.
*/
#include "../../includes/global.h"

int my_tablen(char **tab)
{
    int i = 0;

    if (tab == NULL)
        return 0;
    for (i = 0; tab[i] != NULL; i++);
    return i;
}
