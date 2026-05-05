/*
** EPITECH PROJECT, 2026
** word_array_len.c
** File description:
** Get the length of an array of words
*/
#include <stddef.h>
#include "utils.h"

size_t word_array_len(char **array)
{
    size_t len = 0;

    if (!array)
        return 0;
    while (array[len] != NULL)
        len++;
    return len;
}
