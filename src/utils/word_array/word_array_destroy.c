/*
** EPITECH PROJECT, 2026
** word_array_destroy.c
** File description:
** Free an array of words
*/
#include <stdlib.h>
#include "utils.h"

void word_array_destroy(char ***array)
{
    if (!array || !*array)
        return;
    for (size_t i = 0; (*array)[i] != NULL; i++)
        free((*array)[i]);
    free(*array);
    *array = NULL;
}
