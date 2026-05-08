/*
** EPITECH PROJECT, 2026
** tests_run_ast.c
** File description:
** This file contains unit tests for the run_ast function
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "env.h"
#include "execution.h"
#include "global.h"
#include "lexer.h"
#include "parsing.h"
#include "shell.h"

static void redirect_all_str(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static void setup_default_shell(shell_parameters_t *shell)
{
    char *env[1];

    env[0] = NULL;
    shell_init(shell, env);
    my_setenv(shell, "PATH", "/bin:/usr/bin");
}

Test(run_ast, run_simple_command, .init = cr_redirect_stdout)
{
    shell_parameters_t shell = {0};
    ast_node_t *node = NULL;

    setup_default_shell(&shell);
    node = ast_node_create();
    node->type = NODE_COMMAND;
    node->args = lex_split_words("echo abc");
    cr_assert_eq(run_ast(node, &shell), SUCCESS);
    cr_assert_eq(shell.last_exit_code, 0);
    cr_assert_stdout_eq_str("abc\n");
    shell_clean(&shell);
}

Test(run_ast, run_command_with_or, .init = redirect_all_str)
{
    shell_parameters_t shell = {0};
    ast_node_t *or_node = NULL;
    ast_node_t *left_node = NULL;
    ast_node_t *right_node = NULL;

    setup_default_shell(&shell);
    left_node = ast_node_create();
    left_node->type = NODE_COMMAND;
    left_node->args = lex_split_words("azert");
    right_node = ast_node_create();
    right_node->type = NODE_COMMAND;
    right_node->args = lex_split_words("echo success");
    or_node = ast_node_create();
    or_node->type = NODE_OR;
    or_node->left = left_node;
    or_node->right = right_node;
    cr_assert_eq(run_ast(or_node, &shell), SUCCESS);
    cr_assert_eq(shell.last_exit_code, 0);
    cr_assert_stderr_eq_str("azert: Command not found.\n");
    cr_assert_stdout_eq_str("success\n");
    shell_clean(&shell);
}

Test(run_ast, run_command_with_and, .init = redirect_all_str)
{
    shell_parameters_t shell = {0};
    ast_node_t *and_node = NULL;
    ast_node_t *left_node = NULL;
    ast_node_t *right_node = NULL;

    setup_default_shell(&shell);
    left_node = ast_node_create();
    left_node->type = NODE_COMMAND;
    left_node->args = lex_split_words("echo first");
    right_node = ast_node_create();
    right_node->type = NODE_COMMAND;
    right_node->args = lex_split_words("echo second");
    and_node = ast_node_create();
    and_node->type = NODE_AND;
    and_node->left = left_node;
    and_node->right = right_node;
    cr_assert_eq(run_ast(and_node, &shell), SUCCESS);
    cr_assert_eq(shell.last_exit_code, 0);
    cr_assert_stdout_eq_str("first\nsecond\n");
    shell_clean(&shell);
}

Test(run_ast, run_command_with_sequence, .init = redirect_all_str)
{
    shell_parameters_t shell = {0};
    ast_node_t *seq_node = NULL;
    ast_node_t *first_node = NULL;
    ast_node_t *second_node = NULL;

    setup_default_shell(&shell);
    first_node = ast_node_create();
    first_node->type = NODE_COMMAND;
    first_node->args = lex_split_words("echo first");
    second_node = ast_node_create();
    second_node->type = NODE_COMMAND;
    second_node->args = lex_split_words("echo second");
    seq_node = ast_node_create();
    seq_node->type = NODE_SEQUENCE;
    seq_node->left = first_node;
    seq_node->right = second_node;
    cr_assert_eq(run_ast(seq_node, &shell), SUCCESS);
    cr_assert_eq(shell.last_exit_code, 0);
    cr_assert_stdout_eq_str("first\nsecond\n");
    shell_clean(&shell);
}

Test(run_ast, run_command_with_pipe, .init = redirect_all_str)
{
    shell_parameters_t shell = {0};
    ast_node_t *pipe_node = NULL;
    ast_node_t *left_node = NULL;
    ast_node_t *right_node = NULL;

    setup_default_shell(&shell);
    left_node = ast_node_create();
    left_node->type = NODE_COMMAND;
    left_node->args = lex_split_words("echo hello");
    right_node = ast_node_create();
    right_node->type = NODE_COMMAND;
    right_node->args = lex_split_words("tr a-z A-Z");
    pipe_node = ast_node_create();
    pipe_node->type = NODE_PIPE;
    pipe_node->left = left_node;
    pipe_node->right = right_node;
    cr_assert_eq(run_ast(pipe_node, &shell), SUCCESS);
    cr_assert_eq(shell.last_exit_code, 0);
    cr_assert_stdout_eq_str("HELLO\n");
    shell_clean(&shell);
}
