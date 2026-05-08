/*
** EPITECH PROJECT, 2026
** tests_builtin_repeat.c
** File description:
** This file contains unit tests for the builtin_repeat function
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
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
    my_setenv(shell, "PATH", "/bin:/usr/bin");
    word_array_push(&shell->command, "repeat");
}

Test(builtin_repeat, repeat_command_multiple_times)
{
    shell_parameters_t shell = {0};

    setup_default_shell(&shell);
    word_array_push(&shell.command, "3");
    word_array_push(&shell.command, "echo Hello");
    shell.line = "repeat 3 echo Hello";
    cr_assert_eq(builtin_repeat(&shell, shell.command), COMMAND_FOUND);
    fflush(stdout);
    // cr_assert_stdout_eq_str("Hello\nHello\nHello\n");
    shell_clean(&shell);
}
