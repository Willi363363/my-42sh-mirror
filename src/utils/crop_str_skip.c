/*
** EPITECH PROJECT, 2025
** crop_str_skip.c
** File description:
** Crop a string by skipping a number of characters at the beginning
*/
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *crop_str_skip(char *str, int chars_to_skip)
{
    char *res = malloc((strlen(str) - chars_to_skip + 1));
    int i = 0;

    for (; str[i + chars_to_skip] != '\0'; i++)
        res[i] = str[i + chars_to_skip];
    res[i] = '\0';
    return res;
}
