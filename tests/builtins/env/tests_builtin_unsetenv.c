/*
** EPITECH PROJECT, 2026
** tests_builtin_unsetenv.c
** File description:
** This file contains unit tests for the builtin_unsetenv function
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
    word_array_push(&shell->command, "unsetenv");
}

Test(builtin_unsetenv, unset_existing_variable)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    my_setenv(&shell, "TEST_VAR", "test_value");
    word_array_push(&shell.command, "TEST_VAR");
    cr_assert_eq(builtin_unsetenv(&shell), COMMAND_FOUND);
    cr_assert_null(my_getenv(shell.env, "TEST_VAR"));
    shell_clean(&shell);
}

Test(builtin_unsetenv, unset_nonexistent_variable)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "NONEXISTENT_VAR");
    cr_assert_eq(builtin_unsetenv(&shell), COMMAND_FOUND);
    shell_clean(&shell);
}
