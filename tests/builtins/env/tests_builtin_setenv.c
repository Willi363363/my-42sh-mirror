/*
** EPITECH PROJECT, 2026
** tests_builtin_setenv.c
** File description:
** This file contains unit tests for the builtin_setenv function
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "builtins/env.h"
#include "env.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static void setup_default_shell(shell_parameters_t *shell)
{
    char *env[1];

    env[0] = NULL;
    shell_init(shell, env);
    word_array_push(&shell->command, "setenv");
}

Test(builtin_setenv, set_new_variable)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "TEST_VAR");
    word_array_push(&shell.command, "test_value");
    cr_assert_eq(builtin_setenv(&shell), COMMAND_FOUND);
    cr_assert_str_eq(my_getenv(shell.env, "TEST_VAR"), "test_value");
    shell_clean(&shell);
}

Test(builtin_setenv, update_existing_variable)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    my_setenv(&shell, "TEST_VAR", "initial_value");
    word_array_push(&shell.command, "TEST_VAR");
    word_array_push(&shell.command, "updated_value");
    cr_assert_eq(builtin_setenv(&shell), COMMAND_FOUND);
    cr_assert_str_eq(my_getenv(shell.env, "TEST_VAR"), "updated_value");
    shell_clean(&shell);
}

Test(builtin_setenv, set_variable_with_no_value)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "TEST_VAR");
    cr_assert_eq(builtin_setenv(&shell), COMMAND_FOUND);
    cr_assert_str_eq(my_getenv(shell.env, "TEST_VAR"), "");
    shell_clean(&shell);
}

Test(builtin_setenv, too_many_arguments, .init = cr_redirect_stderr)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "TEST_VAR");
    word_array_push(&shell.command, "test_value");
    word_array_push(&shell.command, "extra_arg");
    cr_assert_eq(builtin_setenv(&shell), COMMAND_FOUND);
    cr_assert_eq(my_getenv(shell.env, "TEST_VAR"), NULL);
    cr_assert_stderr_eq_str("setenv: Too many arguments.\n");
    shell_clean(&shell);
}
