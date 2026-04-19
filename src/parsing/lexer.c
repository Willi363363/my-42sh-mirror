/*
** EPITECH PROJECT, 2025
** lexer.c
** File description:
** This file contains all my main lexer functions.
*/
#include "../includes/global.h"

static void list_checker_3(lexer_t *current, char *analyze_me)
{
    if (my_strcmp(analyze_me, "(") == 0) {
        current->type = TOKEN_LPAREN;
        return;
    }
    if (my_strcmp(analyze_me, ")") == 0) {
        current->type = TOKEN_RPAREN;
        return;
    }
    current->type = TOKEN_WORD;
}

static void list_checker_2(lexer_t *current, char *analyze_me)
{
    if (my_strcmp(analyze_me, "<<") == 0) {
        current->type = TOKEN_REDIR_HEREDOC;
        return;
    }
    if (my_strcmp(analyze_me, "||") == 0) {
        current->type = TOKEN_OR;
        return;
    }
    if (my_strcmp(analyze_me, ";") == 0) {
        current->type = TOKEN_SEMICOLON;
        return;
    }
    if (my_strcmp(analyze_me, "<") == 0) {
        current->type = TOKEN_REDIR_IN;
        return;
    }
    list_checker_3(current, analyze_me);
}

static void list_checker_1(lexer_t *current, char *analyze_me)
{
    if (my_strcmp(analyze_me, "&&") == 0) {
        current->type = TOKEN_AND;
        return;
    }
    if (my_strcmp(analyze_me, "|") == 0) {
        current->type = TOKEN_PIPE;
        return;
    }
    if (my_strcmp(analyze_me, ">") == 0) {
        current->type = TOKEN_REDIR_OUT;
        return;
    }
    if (my_strcmp(analyze_me, ">>") == 0) {
        current->type = TOKEN_REDIR_APPEND;
        return;
    }
    list_checker_2(current, analyze_me);
}

static lexer_t **free_lexer_array(lexer_t **lexer, int count)
{
    for (int i = 0; i < count; i++) {
        free(lexer[i]->value);
        free(lexer[i]);
    }
    free(lexer);
    return NULL;
}

lexer_t **apply_lexer(shell_parameters_t *shell)
{
    int len = my_tablen(shell->command);
    lexer_t **lexer = malloc((len + 1) * sizeof(lexer_t *));
    int i = 0;

    if (!lexer)
        return NULL;
    for (; i < len; i++) {
        lexer[i] = malloc(sizeof(lexer_t));
        if (!lexer[i])
            return free_lexer_array(lexer, i);
        lexer[i]->value = my_strdup(shell->command[i]);
        if (!lexer[i]->value)
            return free_lexer_array(lexer, i + 1);
        list_checker_1(lexer[i], shell->command[i]);
    }
    lexer[i] = NULL;
    return lexer;
}
