/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-42sh-5
** File description:
** which
*/

#include "../../../includes/global.h"

static char *get_command_path(shell_parameters_t *shell, char *command)
{
    char *potential_path = NULL;

    if (command == NULL || shell == NULL)
        return NULL;
    for (size_t i = 0; shell->paths[i] != NULL; i++) {
        potential_path = malloc(MAX_PATH_LEN);
        if (!potential_path)
            return NULL;
        my_strcpy(potential_path, shell->paths[i]);
        my_strcat(potential_path, "/");
        my_strcat(potential_path, command);
        if (access(potential_path, X_OK) == 0) {
            return potential_path;
        }
        free(potential_path);
    }
    return NULL;
}

static void print_which_not_found(shell_parameters_t *shell, char *command)
{
    my_putstr(command);
    my_putstr(": Command not found.\n");
    shell->last_exit_code = 1;
}

static void print_which_path(char *path)
{
    my_putstr(path);
    my_putchar('\n');
}

static int is_builtin(char *cmd)
{
    const char *builtins[] = {"cd", "exit", "echo", "history", "where",
        "repeat", NULL};

    if (!cmd)
        return COMMAND_ERROR;
    for (int i = 0; builtins[i] != NULL; i++) {
        if (my_strcmp(cmd, builtins[i]) == 0) {
            return COMMAND_FOUND;
        }
    }
    return COMMAND_ERROR;
}

static int which_command(shell_parameters_t *shell, int i)
{
    char *cmd_path = NULL;

    if (is_builtin(shell->command[i]) == COMMAND_FOUND) {
        my_putstr(shell->command[i]);
        my_putstr(":  shell built-in command.\n");
    } else {
        cmd_path = get_command_path(shell, shell->command[i]);
        if (cmd_path != NULL)
            print_which_path(cmd_path);
        else
            print_which_not_found(shell, shell->command[i]);
        free(cmd_path);
    }
    return COMMAND_FOUND;
}

int which(shell_parameters_t *shell)
{
    if (!shell)
        return COMMAND_ERROR;
    if (shell->command[1] == NULL) {
        my_putstr("which: Too few arguments.\n");
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
