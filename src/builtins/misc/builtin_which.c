/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-42sh-5
** File description:
** builtin_which
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins/misc.h"
#include "global.h"
#include "shell.h"

static char *get_command_path(shell_parameters_t *shell, char *command)
{
    char *potential_path = NULL;

    if (command == NULL || shell == NULL)
        return NULL;
    for (size_t i = 0; shell->paths[i] != NULL; i++) {
        potential_path = malloc(MAX_PATH_LEN);
        if (!potential_path)
            return NULL;
        strcpy(potential_path, shell->paths[i]);
        strcat(potential_path, "/");
        strcat(potential_path, command);
        if (access(potential_path, X_OK) == 0) {
            return potential_path;
        }
        free(potential_path);
    }
    return NULL;
}

static void print_which_not_found(shell_parameters_t *shell, char *command)
{
    printf("%s: Command not found.\n", command);
    shell->last_exit_code = 1;
}

static void print_which_path(char *path)
{
    printf("%s\n", path);
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

static int which_command(shell_parameters_t *shell, int i)
{
    char *cmd_path = NULL;

    if (is_builtin(shell->command[i]) == COMMAND_FOUND) {
        printf("%s: shell built-in command.\n", shell->command[i]);
        return COMMAND_FOUND;
    }
    cmd_path = get_command_path(shell, shell->command[i]);
    if (cmd_path != NULL)
        print_which_path(cmd_path);
    else
        print_which_not_found(shell, shell->command[i]);
    free(cmd_path);
    return COMMAND_FOUND;
}

int builtin_which(shell_parameters_t *shell)
{
    if (!shell)
        return COMMAND_ERROR;
    if (shell->command[1] == NULL) {
        printf("which: Too few arguments.\n");
        shell->last_exit_code = 1;
        return COMMAND_FOUND;
    }
    shell->last_exit_code = 0;
    for (size_t i = 1; shell->command[i] != NULL; i++) {
        if (which_command(shell, i) == COMMAND_ERROR) {
            return COMMAND_ERROR;
        }
    }
    return COMMAND_FOUND;
}
