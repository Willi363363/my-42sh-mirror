/*
** EPITECH PROJECT, 2026
** where.c
** File description:
** Find the full path of a command.
*/

#include "../../../includes/global.h"

static char *build_full_path(char *dir, char *cmd)
{
    char *full_path = malloc(strlen(dir) + strlen(cmd) + 2);

    if (!full_path)
        return NULL;
    my_strcpy(full_path, dir);
    my_strcat(full_path, "/");
    my_strcat(full_path, cmd);
    return full_path;
}

static int is_builtin(char *cmd)
{
    const char *builtins[] = {"cd", "exit", "echo", "history", "where", NULL};

    for (int i = 0; builtins[i] != NULL; i++) {
        if (my_strcmp(cmd, builtins[i]) == 0) {
            return COMMAND_FOUND;
        }
    }
    return COMMAND_ERROR;
}

static void find_command_paths(shell_parameters_t *shell, int i)
{
    char *full_path = NULL;

    for (int j = 0; shell->paths[j] != NULL; j++) {
        full_path = build_full_path(shell->paths[j], shell->command[i]);
        if (access(full_path, X_OK) == 0) {
            my_putstr(full_path);
            my_putstr("\n");
        }
        free(full_path);
    }
}

int where(shell_parameters_t *shell)
{
    if (!shell)
        return COMMAND_ERROR;
    if (shell->command[1] == NULL) {
        if (my_putstr("where: Too few arguments.\n") == -1) {
            return COMMAND_ERROR;
        }
        shell->last_exit_code = RUNNING;
        return COMMAND_ERROR;
    }
    for (int i = 1; shell->command[i] != NULL; i++) {
        if (is_builtin(shell->command[i]) == COMMAND_FOUND) {
            my_putstr(shell->command[i]);
            my_putstr(" is a shell built-in\n");
        }
        find_command_paths(shell, i);
    }
    return COMMAND_FOUND;
}
