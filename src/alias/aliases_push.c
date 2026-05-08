/*
** EPITECH PROJECT, 2026
** aliases_push.c
** File description:
** Insert a word into an array of aliases
*/
#include <stdlib.h>
#include <string.h>
#include "alias.h"
#include "global.h"
#include "lexer.h"

int aliases_push(alias_t **aliases, char *name, char *value)
{
    size_t len = *aliases ? aliases_len(*aliases) : 0;
    alias_t *new_aliases = NULL;

    new_aliases = malloc((len + 2) * sizeof(alias_t));
    if (!new_aliases)
        return EXIT_FAIL;
    for (size_t i = 0; *aliases && i < len; i++)
        new_aliases[i] = (*aliases)[i];
    new_aliases[len].name = strdup(name);
    new_aliases[len].value = lex_split_words(value);
    new_aliases[len + 1].name = NULL;
    new_aliases[len + 1].value = NULL;
    if (*aliases)
        free(*aliases);
    *aliases = new_aliases;
    return SUCCESS;
}
