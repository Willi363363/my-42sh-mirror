/*
** EPITECH PROJECT, 2026
** tests_builtin_cd.c
** File description:
** This file contains unit tests for the builtin_cd function
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "builtins/misc.h"
#include "env.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static void setup_default_shell(shell_parameters_t *shell)
{
    char *env[1];

    env[0] = NULL;
    shell_init(shell, env);
    word_array_push(&shell->command, "cd");
    my_setenv(shell, "PWD", "/etc");
}

Test(builtin_cd, cd_to_home)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    my_setenv(&shell, "HOME", "/home");
    word_array_push(&shell.command, "~");
    cr_assert_eq(builtin_cd(&shell), COMMAND_FOUND);
    cr_assert_str_eq(my_getenv(shell.env, "PWD"), "/home");
    shell_clean(&shell);
}

Test(builtin_cd, cd_to_oldpwd)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    my_setenv(&shell, "OLDPWD", "/");
    word_array_push(&shell.command, "-");
    cr_assert_eq(builtin_cd(&shell), COMMAND_FOUND);
    cr_assert_str_eq(my_getenv(shell.env, "PWD"), "/");
    shell_clean(&shell);
}

Test(builtin_cd, cd_to_specific_path)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "/usr");
    cr_assert_eq(builtin_cd(&shell), COMMAND_FOUND);
    cr_assert_str_eq(my_getenv(shell.env, "PWD"), "/usr");
    shell_clean(&shell);
}

Test(builtin_cd, cd_with_too_many_arguments, .init = cr_redirect_stderr)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "/usr");
    word_array_push(&shell.command, "extra_arg");
    cr_assert_eq(builtin_cd(&shell), COMMAND_ERROR);
    cr_assert_str_eq(my_getenv(shell.env, "PWD"), "/etc");
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
    shell_clean(&shell);
}

Test(builtin_cd, cd_to_nonexistent_path, .init = cr_redirect_stderr)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "/nonexistent");
    cr_assert_eq(builtin_cd(&shell), COMMAND_ERROR);
    cr_assert_str_eq(my_getenv(shell.env, "PWD"), "/etc");
    cr_assert_stderr_eq_str("/nonexistent: No such file or directory.\n");
    shell_clean(&shell);
}
