/*
** EPITECH PROJECT, 2026
** tests_ast_create.c
** File description:
** This file contains unit tests for the ast_create function
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "builtins/env.h"
#include "env.h"
#include "global.h"
#include "lexer.h"
#include "parsing.h"
#include "shell.h"
#include "utils.h"

static void setup_default_shell(shell_parameters_t *shell)
{
    char *env[1];

    env[0] = NULL;
    shell_init(shell, env);
}

Test(ast_create, create_simple_command)
{
    shell_parameters_t shell = {0};
    ast_node_t *ast = NULL;

    setup_default_shell(&shell);
    shell.command = lex_split_words("echo Hello World");
    cr_assert_eq(ast_create(&ast, lexer_tokenize(&shell)), SUCCESS);
    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, NODE_COMMAND);
    cr_assert_str_eq(ast->args[0], "echo");
    cr_assert_str_eq(ast->args[1], "Hello");
    cr_assert_str_eq(ast->args[2], "World");
    ast_destroy(ast);
    shell_clean(&shell);
}

Test(ast_create, create_command_with_and)
{
    shell_parameters_t shell = {0};
    ast_node_t *ast = NULL;

    setup_default_shell(&shell);
    shell.command = lex_split_words("echo Hello && echo World");
    cr_assert_eq(ast_create(&ast, lexer_tokenize(&shell)), SUCCESS);
    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, NODE_AND);
    cr_assert_str_eq(ast->left->args[0], "echo");
    cr_assert_str_eq(ast->left->args[1], "Hello");
    cr_assert_str_eq(ast->right->args[0], "echo");
    cr_assert_str_eq(ast->right->args[1], "World");
    ast_destroy(ast);
    shell_clean(&shell);
}
