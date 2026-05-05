/*
** EPITECH PROJECT, 2026
** lexer_destroy.c
** File description:
** Free an array of lexer_t structures
*/
#include <stdlib.h>
#include "lexer.h"

void lexer_destroy(lexer_t **nodes)
{
    if (!nodes)
        return;
    for (int i = 0; nodes[i] != NULL; i++) {
        free(nodes[i]->value);
        free(nodes[i]);
    }
    free(nodes);
}
