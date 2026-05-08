/*
** EPITECH PROJECT, 2026
** tests_builtin_alias.c
** File description:
** This file contains unit tests for the builtin_alias function
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "builtins/misc.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static void setup_default_shell(shell_parameters_t *shell)
{
    char *env[1];

    env[0] = NULL;
    shell_init(shell, env);
    word_array_push(&shell->command, "alias");
    aliases_push(&shell->aliases, "l", "ls -la");
}

Test(builtin_alias, print_existing_alias, .init = cr_redirect_stdout)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "l");
    cr_assert_eq(builtin_alias(&shell), COMMAND_FOUND);
    shell_clean(&shell);
}

Test(builtin_alias, print_nonexistent_alias)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "nonexistent");
    cr_assert_eq(builtin_alias(&shell), COMMAND_ERROR);
    shell_clean(&shell);
}

Test(builtin_alias, create_new_alias)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "newalias");
    word_array_push(&shell.command, "echo Hello");
    cr_assert_eq(builtin_alias(&shell), COMMAND_FOUND);
    cr_assert_str_eq(shell.aliases[1].name, "newalias");
    cr_assert_str_eq(shell.aliases[1].value[0], "echo");
    cr_assert_str_eq(shell.aliases[1].value[1], "Hello");
    shell_clean(&shell);
}

Test(builtin_alias, too_few_arguments)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    cr_assert_eq(builtin_alias(&shell), COMMAND_ERROR);
    shell_clean(&shell);
}
