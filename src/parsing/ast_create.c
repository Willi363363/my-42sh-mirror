/*
** EPITECH PROJECT, 2025
** ast_create.c
** File description:
** This file contains all my main parsing functions.
*/
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "lexer.h"
#include "parsing.h"

static int is_cmd_arg_token(lexer_id_t type)
{
    return type == TOKEN_WORD || type == TOKEN_ENV_VAR;
}

static void check_redirect(size_t *pos, lexer_t **lexer, ast_node_t *new)
{
    switch (lexer[(*pos)]->type) {
        case TOKEN_REDIR_OUT:
            new->type = NODE_REDIR_OUT;
            break;
        case TOKEN_REDIR_APPEND:
            new->type = NODE_REDIR_APPEND;
            break;
        case TOKEN_REDIR_IN:
            new->type = NODE_REDIR_IN;
            break;
        default:
            new->type = NODE_REDIR_OUT;
            break;
    }
}

static void create_full_word(size_t *pos, lexer_t **lexer, ast_node_t *new)
{
    int count = 0;
    int pos_copy = (*pos);
    char **args = NULL;

    for (; lexer[pos_copy] != NULL && is_cmd_arg_token(lexer[pos_copy]->type);
        pos_copy++)
        count++;
    args = malloc((count + 1) * sizeof(char *));
    for (int i = 0;
        lexer[(*pos)] != NULL && is_cmd_arg_token(lexer[(*pos)]->type);
        (*pos)++) {
        args[i] = strdup(lexer[(*pos)]->value);
        i++;
    }
    args[count] = NULL;
    new->args = args;
    new->type = NODE_COMMAND;
}

static ast_node_t *parse_primary(size_t *pos, lexer_t **lexer)
{
    ast_node_t *new = NULL;

    if (lexer[*pos] == NULL)
        return NULL;
    if (lexer[*pos]->type == TOKEN_LPAREN) {
        (*pos)++;
        new = ast_create_rec(pos, lexer);
        if (lexer[*pos] != NULL && lexer[*pos]->type == TOKEN_RPAREN)
            (*pos)++;
        return new;
    }
    if (is_cmd_arg_token(lexer[*pos]->type)) {
        new = ast_node_create();
        if (!new)
            return NULL;
        create_full_word(pos, lexer, new);
        return new;
    }
    return NULL;
}

static ast_node_t *parse_redirection(size_t *pos, lexer_t **lexer)
{
    ast_node_t *left = parse_primary(pos, lexer);
    ast_node_t *new = NULL;

    while (lexer[*pos] != NULL
        && (lexer[(*pos)]->type == TOKEN_REDIR_OUT
            || lexer[(*pos)]->type == TOKEN_REDIR_APPEND
            || lexer[(*pos)]->type == TOKEN_REDIR_IN
            || lexer[(*pos)]->type == TOKEN_REDIR_HEREDOC)) {
        new = ast_node_create();
        check_redirect(pos, lexer, new);
        (*pos)++;
        new->left = left;
        new->right = parse_primary(pos, lexer);
        left = new;
    }
    return left;
}

static ast_node_t *parse_pipeline(size_t *pos, lexer_t **lexer)
{
    ast_node_t *left = parse_redirection(pos, lexer);
    ast_node_t *new = NULL;

    if (lexer[*pos] != NULL && lexer[(*pos)]->type == TOKEN_PIPE) {
        (*pos)++;
        new = ast_node_create();
        new->type = NODE_PIPE;
        new->left = left;
        new->right = parse_pipeline(pos, lexer);
        return new;
    }
    return left;
}

static ast_node_t *parse_logical(size_t *pos, lexer_t **lexer)
{
    ast_node_t *left = parse_pipeline(pos, lexer);
    ast_node_t *new = NULL;

    if (lexer[*pos] != NULL
        && (lexer[(*pos)]->type == TOKEN_AND
            || lexer[(*pos)]->type == TOKEN_OR)) {
        new = ast_node_create();
        if (lexer[(*pos)]->type == TOKEN_AND)
            new->type = NODE_AND;
        else
            new->type = NODE_OR;
        (*pos)++;
        new->left = left;
        new->right = parse_logical(pos, lexer);
        return new;
    }
    return left;
}

ast_node_t *ast_create_rec(size_t *pos, lexer_t **lexer)
{
    ast_node_t *left = parse_logical(pos, lexer);
    ast_node_t *new = NULL;

    if (lexer[*pos] != NULL && lexer[(*pos)]->type == TOKEN_SEMICOLON) {
        (*pos)++;
        new = ast_node_create();
        new->type = NODE_SEQUENCE;
        new->left = left;
        new->right = ast_create_rec(pos, lexer);
        return new;
    }
    return left;
}

int ast_create(ast_node_t **ast, lexer_t **tokens)
{
    size_t pos = 0;

    if (!tokens || !tokens[0])
        return SUCCESS;
    *ast = ast_create_rec(&pos, tokens);
    return SUCCESS;
}
