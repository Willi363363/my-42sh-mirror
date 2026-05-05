/*
** EPITECH PROJECT, 2026
** word_array_duplicate.c
** File description:
** Duplicate an array of words
*/
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char **word_array_duplicate(char **array)
{
    size_t len = word_array_len(array);
    char **new_array = malloc((len + 1) * sizeof(char *));

    if (!new_array)
        return NULL;
    for (size_t i = 0; i < len; i++) {
        new_array[i] = strdup(array[i]);
        if (!new_array[i]) {
            word_array_destroy(&new_array);
            return NULL;
        }
    }
    new_array[len] = NULL;
    return new_array;
}
