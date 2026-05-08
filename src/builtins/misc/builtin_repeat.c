/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-42sh-5
** File description:
** builtin_repeat.c
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins/misc.h"
#include "global.h"
#include "lexer.h"
#include "parsing.h"
#include "shell.h"
#include "utils.h"

static bool invalid_repeat_args(char **parsed_args)
{
    if (parsed_args == NULL)
        return true;
    if (parsed_args[1] == NULL || parsed_args[2] == NULL)
        return true;
    return false;
}

static int parse_repeat_count(char **parsed_args, int *count)
{
    if (invalid_repeat_args(parsed_args)) {
        fprintf(stderr, "repeat: Too few arguments.\n");
        return EXIT_FAIL;
    }
    *count = atoi(parsed_args[1]);
    if (*count <= 0) {
        fprintf(stderr, "repeat: Invalid count '%s'.\n", parsed_args[1]);
        return EXIT_FAIL;
    }
    return SUCCESS;
}

static char *build_subcommand_line(char **args, int start)
{
    char *sub_line = NULL;
    size_t len = 0;

    for (int i = start; args[i] != NULL; i++) {
        len += strlen(args[i]);
        if (args[i + 1] != NULL)
            len++;
    }
    sub_line = malloc(len + 1);
    if (sub_line == NULL)
        return NULL;
    sub_line[0] = '\0';
    for (int i = start; args[i] != NULL; i++) {
        strcat(sub_line, args[i]);
        if (args[i + 1] != NULL)
            strcat(sub_line, " ");
    }
    return sub_line;
}

static int run_repeat_loop(shell_parameters_t *shell,
    char *sub_line,
    int count)
{
    int result = SUCCESS;
    char **saved_cmd = shell->command;
    char *saved_line = shell->line;

    shell->line = sub_line;
    for (int i = 0; i < count; i++) {
        shell->command = lex_split_words(shell->line);
        safe_free((void **)&shell->command_real_path);
        if (shell->command == NULL) {
            result = EXIT_FAIL;
            break;
        }
        result = handle_cmd_parsing(shell);
        word_array_destroy(&shell->command);
        if (result != SUCCESS)
            break;
    }
    shell->command = saved_cmd;
    shell->line = saved_line;
    return result;
}

static int build_repeat_context(shell_parameters_t *shell,
    char **sub_line,
    int *count)
{
    if (parse_repeat_count(shell->command, count) == EXIT_FAIL) {
        shell->last_exit_code = 1;
        return EXIT_FAIL;
    }
    *sub_line = build_subcommand_line(shell->command, 2);
    if (*sub_line == NULL) {
        shell->last_exit_code = 1;
        return EXIT_FAIL;
    }
    return SUCCESS;
}

int builtin_repeat(shell_parameters_t *shell, char **args)
{
    int count = 0;
    int loop_status = SUCCESS;
    char *sub_line = NULL;

    (void)args;
    if (build_repeat_context(shell, &sub_line, &count) ==
        EXIT_FAIL) {
        return COMMAND_ERROR;
    }
    loop_status = run_repeat_loop(shell, sub_line, count);
    free(sub_line);
    if (loop_status != SUCCESS)
        return COMMAND_ERROR;
    return COMMAND_FOUND;
}
