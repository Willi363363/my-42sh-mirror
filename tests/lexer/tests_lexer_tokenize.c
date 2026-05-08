/*
** EPITECH PROJECT, 2026
** tests_lex_split_words.c
** File description:
** This file contains unit tests for the lex_split_words function.
*/
#include <criterion/criterion.h>
#include "lexer.h"
#include "shell.h"
#include "utils.h"

static void setup_default_shell(shell_parameters_t *shell)
{
    char *env[1];

    env[0] = NULL;
    shell_init(shell, env);
    word_array_push(&shell->command, "ls");
    word_array_push(&shell->command, "-l");
    word_array_push(&shell->command, "&&");
    word_array_push(&shell->command, "echo");
    word_array_push(&shell->command, "Hello");
}

Test(lexer_tokenize, simple_command)
{
    shell_parameters_t shell = {0};
    lexer_t **tokens = NULL;

    setup_default_shell(&shell);
    tokens = lexer_tokenize(&shell);
    cr_assert_eq(tokens[0]->type, TOKEN_WORD);
    cr_assert_str_eq(tokens[0]->value, "ls");
    cr_assert_eq(tokens[1]->type, TOKEN_WORD);
    cr_assert_str_eq(tokens[1]->value, "-l");
    cr_assert_eq(tokens[2]->type, TOKEN_AND);
    cr_assert_eq(tokens[3]->type, TOKEN_WORD);
    cr_assert_str_eq(tokens[3]->value, "echo");
    cr_assert_eq(tokens[4]->type, TOKEN_WORD);
    cr_assert_str_eq(tokens[4]->value, "Hello");
    cr_assert_null(tokens[5]);
    lexer_destroy(tokens);
}
