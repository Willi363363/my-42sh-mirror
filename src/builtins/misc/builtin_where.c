/*
** EPITECH PROJECT, 2026
** builtin_where.c
** File description:
** Find the full path of a command.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins/misc.h"
#include "env.h"
#include "global.h"
#include "shell.h"
#include "utils.h"

static char *build_full_path(char *dir, char *cmd)
{
    char *full_path = NULL;

    if (!dir || !cmd)
        return NULL;
    full_path = malloc(strlen(dir) + strlen(cmd) + 2);
    if (!full_path)
        return NULL;
    strcpy(full_path, dir);
    strcat(full_path, "/");
    strcat(full_path, cmd);
    return full_path;
}

static int is_builtin(char *cmd)
{
    const char *builtins[] =
    {"cd", "exit", "echo", "history", "where", "repeat", NULL};

    if (!cmd)
        return COMMAND_ERROR;
    for (int i = 0; builtins[i] != NULL; i++) {
        if (strcmp(cmd, builtins[i]) == 0) {
            return COMMAND_FOUND;
        }
    }
    return COMMAND_ERROR;
}

static int find_command_paths(shell_parameters_t *shell, int i)
{
    char *full_path = NULL;
    int found = 0;
    char **paths = env_get_paths(shell);

    if (!shell || !paths)
        return 0;
    for (int j = 0; paths[j] != NULL; j++) {
        full_path = build_full_path(paths[j], shell->command[i]);
        if (full_path != NULL && access(full_path, X_OK) == 0) {
            printf("%s\n", full_path);
            found = 1;
        }
        free(full_path);
    }
    word_array_destroy(&paths);
    return found;
}

static void print_where_builtin(char *command)
{
    printf("%s is a shell built-in\n", command);
}

static void print_where_not_found(shell_parameters_t *shell, char *command)
{
    printf("%s: Command not found.\n", command);
    shell->last_exit_code = 1;
}

static int where_too_few_arguments(shell_parameters_t *shell)
{
    if (printf("where: Too few arguments.\n") == -1)
        return COMMAND_ERROR;
    shell->last_exit_code = 1;
    return COMMAND_ERROR;
}

static void process_where_command(shell_parameters_t *shell, int i)
{
    int found = 0;

    if (is_builtin(shell->command[i]) == COMMAND_FOUND) {
        print_where_builtin(shell->command[i]);
        found = 1;
    }
    if (find_command_paths(shell, i) == 1)
        found = 1;
    if (found == 0)
        print_where_not_found(shell, shell->command[i]);
}

int builtin_where(shell_parameters_t *shell)
{
    if (!shell)
        return COMMAND_ERROR;
    if (shell->command[1] == NULL) {
        return where_too_few_arguments(shell);
    }
    shell->last_exit_code = 0;
    for (int i = 1; shell->command[i] != NULL; i++) {
        process_where_command(shell, i);
    }
    return COMMAND_FOUND;
}
