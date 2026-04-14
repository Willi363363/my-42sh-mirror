/*
** EPITECH PROJECT, 2025
** parsing.c
** File description:
** This file contains all my main parsing functions.
*/
#include "../includes/global.h"

static ast_node_t *init_ast_node(void)
{
    ast_node_t *new = malloc(sizeof(ast_node_t));

    if (!new)
        return NULL;
    *new = (ast_node_t){0};
    return new;
}

static void check_redirect(int *pos, lexer_t **lexer, ast_node_t *new)
{
    switch (lexer[(*pos)]->type) {
        case TOKEN_REDIR_OUT :
            new->type = NODE_REDIR_OUT;
            break;
        case TOKEN_REDIR_APPEND :
            new->type = NODE_REDIR_APPEND;
            break;
        case TOKEN_REDIR_IN :
            new->type = NODE_REDIR_IN;
            break;
        default :
            new->type = NODE_REDIR_OUT;
            break;
    }
}

static void create_full_word(int *pos, lexer_t **lexer, ast_node_t *new)
{
    int count = 0;
    int pos_copy = (*pos);
    char **args = NULL;

    for (; lexer[pos_copy] != NULL &&
        lexer[pos_copy]->type == TOKEN_WORD; pos_copy++)
        count++;
    args = malloc((count + 1) * sizeof(char *));
    for (int i = 0; lexer[(*pos)] != NULL &&
        lexer[(*pos)]->type == TOKEN_WORD; (*pos)++) {
        args[i] = my_strdup(lexer[(*pos)]->value);
        i++;
    }
    args[count] = NULL;
    new->args = args;
    new->type = NODE_COMMAND;
}

static ast_node_t *parse_primary(int *pos, lexer_t **lexer)
{
    ast_node_t *new = NULL;

    if (lexer[*pos] == NULL)
        return NULL;
    if (lexer[*pos]->type == TOKEN_LPAREN) {
        (*pos)++;
        new = parse_list(pos, lexer);
        if (lexer[*pos] != NULL && lexer[*pos]->type == TOKEN_RPAREN)
            (*pos)++;
        return new;
    }
    if (lexer[*pos]->type == TOKEN_WORD) {
        new = init_ast_node();
        if (!new)
            return NULL;
        create_full_word(pos, lexer, new);
        return new;
    }
    return NULL;
}

static ast_node_t *parse_redirection(int *pos, lexer_t **lexer)
{
    ast_node_t *left = parse_primary(pos, lexer);
    ast_node_t *new = NULL;

    while (lexer[*pos] != NULL && (lexer[(*pos)]->type == TOKEN_REDIR_OUT
            || lexer[(*pos)]->type == TOKEN_REDIR_APPEND ||
            lexer[(*pos)]->type == TOKEN_REDIR_IN ||
            lexer[(*pos)]->type == TOKEN_REDIR_HEREDOC)) {
        new = init_ast_node();
        check_redirect(pos, lexer, new);
        (*pos)++;
        new->left = left;
        new->right = parse_primary(pos, lexer);
        left = new;
    }
    return left;
}

static ast_node_t *parse_pipeline(int *pos, lexer_t **lexer)
{
    ast_node_t *left = parse_redirection(pos, lexer);
    ast_node_t *new = NULL;

    if (lexer[*pos] != NULL && lexer[(*pos)]->type == TOKEN_PIPE) {
        (*pos)++;
        new = init_ast_node();
        new->type = NODE_PIPE;
        new->left = left;
        new->right = parse_pipeline(pos, lexer);
        return new;
    }
    return left;
}

static ast_node_t *parse_logical(int *pos, lexer_t **lexer)
{
    ast_node_t *left = parse_pipeline(pos, lexer);
    ast_node_t *new = NULL;

    if (lexer[*pos] != NULL && (lexer[(*pos)]->type == TOKEN_AND
            || lexer[(*pos)]->type == TOKEN_OR)) {
        new = init_ast_node();
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

ast_node_t *parse_list(int *pos, lexer_t **lexer)
{
    ast_node_t *left = parse_logical(pos, lexer);
    ast_node_t *new = NULL;

    if (lexer[*pos] != NULL && lexer[(*pos)]->type == TOKEN_SEMICOLON) {
        (*pos)++;
        new = init_ast_node();
        new->type = NODE_SEQUENCE;
        new->left = left;
        new->right = parse_list(pos, lexer);
        return new;
    }
    return left;
}

int apply_parser(ast_node_t **ast, lexer_t **tokens)
{
    int pos = 0;

    if (!tokens || !tokens[0])
        return SUCCESS;
    *ast = parse_list(&pos, tokens);
    return SUCCESS;
}

int execute_ast(shell_parameters_t *shell)
{
    int found = 0;
    int result = 0;
    ast_node_t *ast = NULL;
    lexer_t **lexer = apply_lexer(shell);

    if (!lexer)
        return EXIT_FAIL;
    found = apply_parser(&ast, lexer);
    result = run_ast(ast, shell);
    free_lexer(lexer);
    free_ast(ast);
    if (found != SUCCESS)
        return found;
    else
        return result;
}
