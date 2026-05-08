/*
** EPITECH PROJECT, 2026
** tests_builtin_history.c
** File description:
** This file contains unit tests for the builtin_history function
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "builtins/misc.h"
#include "env.h"
#include "global.h"
#include "history.h"
#include "shell.h"
#include "utils.h"

static void setup_default_shell(shell_parameters_t *shell)
{
    char *env[1];
    char *cwd = getcwd(NULL, 0);

    env[0] = NULL;
    shell_init(shell, env);
    my_setenv(shell, "HOME", cwd);
    my_setenv(shell, "PWD", cwd);
    word_array_push(&shell->command, "history");
}

Test(builtin_history, print_history, .init = cr_redirect_stdout)
{
    shell_parameters_t shell = {0};
    char *history_path = NULL;

    setup_default_shell(&shell);
    push_to_history(&shell);
    cr_assert_eq(builtin_history(&shell), COMMAND_FOUND);
    fflush(stdout);
    cr_assert_stdout_eq_str("1  history\n");
    history_path = get_history_path(&shell);
    if (history_path) {
        unlink(history_path);
        free(history_path);
    }
    shell_clean(&shell);
}
