/*
** EPITECH PROJECT, 2026
** expand_aliases.c
** File description:
** Expand aliases in the command arguments before execution
*/
#include <dirent.h>
#include <glob.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "expansion.h"
#include "shell.h"
#include "utils.h"

static void handle_alias_expansion(shell_parameters_t *shell, char ***cmd)
{
    char *alias_name = (*cmd)[0];
    char **alias_value = NULL;

    for (size_t i = 0; shell->aliases[i].name; i++) {
        if (strcmp(shell->aliases[i].name, alias_name) == 0) {
            alias_value = shell->aliases[i].value;
            break;
        }
    }
    if (!alias_value)
        return;
    word_array_remove(cmd, 0);
    for (ssize_t i = word_array_len(alias_value) - 1; i >= 0; i--)
        word_array_insert(cmd, alias_value[i], 0);
}

void expand_aliases(shell_parameters_t *shell, char ***cmd)
{
    if (!cmd || !(*cmd) || !shell || !shell->aliases)
        return;
    handle_alias_expansion(shell, cmd);
}
