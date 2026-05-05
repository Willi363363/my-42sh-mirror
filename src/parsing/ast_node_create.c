/*
** EPITECH PROJECT, 2026
** ast_node_create.c
** File description:
** Create an AST node
*/
#include <stdlib.h>
#include "parsing.h"

ast_node_t *ast_node_create(void)
{
    ast_node_t *new = malloc(sizeof(ast_node_t));

    if (!new)
        return NULL;
    *new = (ast_node_t){0};
    return new;
}
