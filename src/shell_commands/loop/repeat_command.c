/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-42sh-5
** File description:
** repeat_command
*/

#include "global.h"

static void free_parsed_args(char **parsed_args)
{
    if (parsed_args == NULL)
        return;
    for (int i = 0; parsed_args[i] != NULL; i++) {
        free(parsed_args[i]);
        parsed_args[i] = NULL;
    }
    free(parsed_args);
}

static int invalid_repeat_args(char **parsed_args)
{
    return parsed_args == NULL || parsed_args[1] == NULL ||
        parsed_args[2] == NULL;
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

static int args_total_len(char **args, int start)
{
    int len = 0;

    for (int i = start; args[i] != NULL; i++) {
        len += my_strlen(args[i]);
        if (args[i + 1] != NULL)
            len++;
    }
    return len;
}

static char *build_subcommand_line(char **args, int start)
{
    int len = args_total_len(args, start);
    char *line = NULL;

    line = malloc((len + 1) * sizeof(char));
    if (line == NULL)
        return NULL;
    line[0] = '\0';
    for (int i = start; args[i] != NULL; i++) {
        my_strcat(line, args[i]);
        if (args[i + 1] != NULL)
            my_strcat(line, " ");
    }
    return line;
}

static int run_repeat_loop(shell_parameters_t *shell,
    char **parsed_args, char *sub_line, int count)
{
    int result = SUCCESS;
    char **saved_cmd = shell->command;
    char *saved_line = shell->line;

    for (int i = 0; i < count; i++) {
        shell->command = parsed_args + 2;
        shell->line = sub_line;
        my_safe_free((void **)&shell->command_real_path);
        result = commands_launcher(shell);
        if (result != SUCCESS)
            break;
    }
    shell->command = saved_cmd;
    shell->line = saved_line;
    return result;
}

static int build_repeat_context(shell_parameters_t *shell,
    char ***parsed_args, char **sub_line, int *count)
{
    *parsed_args = my_str_to_word_array(shell->line);
    if (parse_repeat_count(*parsed_args, count) == EXIT_FAIL) {
        shell->last_exit_code = 1;
        return EXIT_FAIL;
    }
    *sub_line = build_subcommand_line(*parsed_args, 2);
    if (*sub_line == NULL) {
        shell->last_exit_code = 1;
        return EXIT_FAIL;
    }
    return SUCCESS;
}

int repeat_command(shell_parameters_t *shell, char **args)
{
    int count = 0;
    int loop_status = SUCCESS;
    char **parsed_args = NULL;
    char *sub_line = NULL;

    (void)args;
    if (build_repeat_context(shell, &parsed_args, &sub_line, &count)
        == EXIT_FAIL) {
        free_parsed_args(parsed_args);
        return COMMAND_ERROR;
    }
    loop_status = run_repeat_loop(shell, parsed_args, sub_line, count);
    free(sub_line);
    free_parsed_args(parsed_args);
    if (loop_status != SUCCESS)
        return COMMAND_ERROR;
    return COMMAND_FOUND;
}
