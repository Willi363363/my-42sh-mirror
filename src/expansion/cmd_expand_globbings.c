/*
** EPITECH PROJECT, 2025
** cmd_expand_globbings.c
** File description:
** Expand environment variables inside command arguments.
*/
#include <dirent.h>
#include <glob.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "expansion.h"
#include "shell.h"
#include "utils.h"

static void handle_globbings_expansion(shell_parameters_t *shell,
    char ***cmd,
    size_t *index)
{
    char *pattern = (*cmd)[*index];
    glob_t results = {0};

    chdir(shell->pwd);
    if (glob(pattern, 0, NULL, &results) != 0 || results.gl_pathc == 0) {
        globfree(&results);
        return;
    }
    word_array_remove(cmd, *index);
    for (ssize_t i = results.gl_pathc - 1; i >= 0; i--)
        word_array_insert(cmd, results.gl_pathv[i], *index);
    *index += results.gl_pathc - 1;
    globfree(&results);
}

void cmd_expand_globbings(shell_parameters_t *shell, char ***cmd)
{
    if (!cmd || !(*cmd) || !shell || !shell->env)
        return;
    for (size_t i = 1; (*cmd)[i] != NULL; i++) {
        handle_globbings_expansion(shell, cmd, &i);
    }
}
