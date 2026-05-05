/*
** EPITECH PROJECT, 2026
** word_array_remove.c
** File description:
** Remove a word from an array of words at a specified index
*/
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "shell.h"
#include "utils.h"

int word_array_remove(char ***array, size_t index)
{
    size_t len = *array ? word_array_len(*array) : 0;
    char **new_array = NULL;
    int j = 0;

    if (index < 0 || (size_t)index >= len)
        return EXIT_FAIL;
    new_array = malloc(len * sizeof(char *));
    if (!new_array)
        return EXIT_FAIL;
    for (size_t i = 0; i < len; i++) {
        if (i == index)
            continue;
        new_array[j] = (*array)[i];
        j++;
    }
    free((*array)[index]);
    new_array[len - 1] = NULL;
    free(*array);
    *array = new_array;
    return SUCCESS;
}
