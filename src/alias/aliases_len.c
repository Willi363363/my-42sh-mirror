/*
** EPITECH PROJECT, 2026
** aliases_len.c
** File description:
** Get the length of an array of words
*/
#include <stddef.h>
#include "alias.h"

size_t aliases_len(alias_t *aliases)
{
    size_t len = 0;

    if (!aliases)
        return 0;
    while (aliases[len].name)
        len++;
    return len;
}
