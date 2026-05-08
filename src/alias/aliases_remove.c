/*
** EPITECH PROJECT, 2026
** aliases_remove.c
** File description:
** Remove a word from an array of aliases at a specified index
*/
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "shell.h"

int aliases_remove(alias_t **aliases, size_t index)
{
    size_t len = *aliases ? aliases_len(*aliases) : 0;
    alias_t *new_aliases = NULL;
    int j = 0;

    if (index < 0 || (size_t)index >= len)
        return EXIT_FAIL;
    new_aliases = malloc(len * sizeof(alias_t));
    if (!new_aliases)
        return EXIT_FAIL;
    for (size_t i = 0; i < len; i++) {
        if (i == index)
            continue;
        new_aliases[j] = (*aliases)[i];
        j++;
    }
    new_aliases[len - 1].name = NULL;
    new_aliases[len - 1].value = NULL;
    free(*aliases);
    *aliases = new_aliases;
    return SUCCESS;
}
