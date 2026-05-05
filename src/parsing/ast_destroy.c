/*
** EPITECH PROJECT, 2026
** ast_destroy.c
** File description:
** Destroy an AST node and all its children
*/
#include <stdlib.h>
#include "parsing.h"

void ast_destroy(ast_node_t *ast)
{
    if (!ast)
        return;
    ast_destroy(ast->left);
    ast_destroy(ast->right);
    if (ast->args != NULL) {
        for (int i = 0; ast->args[i] != NULL; i++)
            free(ast->args[i]);
        free(ast->args);
    }
    free(ast->input_file);
    free(ast->output_file);
    free(ast);
}
