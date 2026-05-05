/*
** EPITECH PROJECT, 2026
** exec_command.c
** File description:
** Execute a command node in the AST.
*/
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parsing.h"
#include "shell.h"
#include "utils.h"

int exec_command(ast_node_t *node, shell_parameters_t *shell)
{
    char **saved_cmd = shell->command;
    int found = 0;

    shell->command = word_array_duplicate(node->args);
    found = shell_exec_cmd(shell);
    word_array_destroy(&shell->command);
    shell->command = saved_cmd;
    return found;
}
