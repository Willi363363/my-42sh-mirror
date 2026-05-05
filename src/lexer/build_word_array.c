/*
** EPITECH PROJECT, 2026
** build_word_array.c
** File description:
** This file contains the function that builds an array of words
*/
#include <stdlib.h>
#include "global.h"
#include "lexer.h"
#include "shell.h"

static char *copy_word(char *src, int start, int size)
{
    char *word = malloc(size + 1);
    int i = 0;

    if (!word)
        return NULL;
    while (i < size) {
        word[i] = src[start + i];
        i++;
    }
    word[size] = '\0';
    return word;
}

static void free_word_array(char **res)
{
    if (!res)
        return;
    for (int i = 0; res[i]; i++)
        free(res[i]);
    free(res);
}

int build_word_array(char *str, char **res)
{
    size_t i = 0;
    size_t res_i = 0;
    int wsize = 0;
    int start = 0;

    for (; str[i] != '\0'; res_i++) {
        wsize = 0;
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] == '\0')
            break;
        i = process_word(str, i, &start, &wsize);
        res[res_i] = copy_word(str, start, wsize);
        if (!res[res_i]) {
            free_word_array(res);
            return EXIT_FAIL;
        }
    }
    res[res_i] = NULL;
    return SUCCESS;
}
