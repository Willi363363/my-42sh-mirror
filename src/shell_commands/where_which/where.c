/*
** EPITECH PROJECT, 2026
** where.c
** File description:
** Find the full path of a command.
*/

#include "../../../includes/global.h"

static char *build_full_path(char *dir, char *cmd)
{
    char *full_path = NULL;

    if (!dir || !cmd)
        return NULL;
    full_path = malloc(strlen(dir) + strlen(cmd) + 2);
    if (!full_path)
        return NULL;
    my_strcpy(full_path, dir);
    my_strcat(full_path, "/");
    my_strcat(full_path, cmd);
    return full_path;
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

static int find_command_paths(shell_parameters_t *shell, int i)
{
    char *full_path = NULL;
    int found = 0;

    if (!shell || !shell->paths)
        return 0;
    for (int j = 0; shell->paths[j] != NULL; j++) {
        full_path = build_full_path(shell->paths[j], shell->command[i]);
        if (full_path != NULL && access(full_path, X_OK) == 0) {
            my_putstr(full_path);
            my_putstr("\n");
            found = 1;
        }
        free(full_path);
    }
    return found;
}

static void print_where_builtin(char *command)
{
    my_putstr(command);
    my_putstr(" is a shell built-in\n");
}

static void print_where_not_found(shell_parameters_t *shell, char *command)
{
    my_putstr(command);
    my_putstr(": Command not found.\n");
    shell->last_exit_code = 1;
}

static int where_too_few_arguments(shell_parameters_t *shell)
{
    if (my_putstr("where: Too few arguments.\n") == -1)
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

int where(shell_parameters_t *shell)
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
