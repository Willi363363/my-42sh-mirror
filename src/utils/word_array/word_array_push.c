/*
** EPITECH PROJECT, 2026
** word_array_push.c
** File description:
** push a word into an array of words at a specified index
*/
#include <stdlib.h>
#include "utils.h"

int word_array_push(char ***array, char *word)
{
    size_t len = *array ? word_array_len(*array) : 0;

    return word_array_insert(array, word, len);
}
