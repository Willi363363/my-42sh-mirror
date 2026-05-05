/*
** EPITECH PROJECT, 2026
** word_array_insert.c
** File description:
** Insert a word into an array of words at a specified index
*/
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "shell.h"
#include "utils.h"

int word_array_insert(char ***array, char *word, size_t index)
{
    size_t len = *array ? word_array_len(*array) : 0;
    char **new_array = NULL;

    if (index < 0 || index > len)
        return EXIT_FAIL;
    new_array = malloc((len + 2) * sizeof(char *));
    if (!new_array)
        return EXIT_FAIL;
    for (size_t i = 0; *array && i < index; i++)
        new_array[i] = (*array)[i];
    new_array[index] = strdup(word);
    for (size_t i = index; *array && i < len; i++)
        new_array[i + 1] = (*array)[i];
    new_array[len + 1] = NULL;
    if (*array)
        free(*array);
    *array = new_array;
    return SUCCESS;
}
