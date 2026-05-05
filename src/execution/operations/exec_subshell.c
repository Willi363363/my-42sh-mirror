/*
** EPITECH PROJECT, 2026
** exec_subshell.c
** File description:
** Execute a subshell node in the AST.
*/
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include "execution.h"
#include "global.h"
#include "parsing.h"
#include "shell.h"

int exec_subshell(ast_node_t *node, shell_parameters_t *shell)
{
    (void)node;
    (void)shell;
    return SUCCESS;
}
