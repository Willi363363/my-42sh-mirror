/*
** EPITECH PROJECT, 2025
** env_cmds.c
** File description:
** This file contains all my envs commands functions.
*/
#include "../../../includes/global.h"

static int replace_current_env_var(shell_parameters_t *shell,
    char *cmd, int i)
{
    my_safe_free((void **)&shell->env[i]);
    shell->env[i] = my_strdup(cmd);
    return COMMAND_FOUND;
}

static int check_if_env_var_exists(shell_parameters_t *shell, char *cmd)
{
    char *cmd_copy = my_strdup(cmd);
    char *env_var = strtok(cmd_copy, "=");
    int found = 0;

    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(env_var, shell->env[i], my_strlen(env_var)) == 0 &&
            shell->env[i][my_strlen(env_var)] == '=')
            found = replace_current_env_var(shell, cmd, i);
    }
    my_safe_free((void **)&cmd_copy);
    if (found == 0)
        return EXIT_FAIL;
    return SUCCESS;
}

static int create_new_env_var(shell_parameters_t *shell, char *cmd)
{
    int i = 0;
    char **new_env = NULL;

    for (; shell->env[i] != NULL; i++);
    new_env = malloc(sizeof(char *) * (i + 2));
    if (new_env == NULL)
        return EXIT_FAIL;
    for (int j = 0; j < i; j++)
        new_env[j] = shell->env[j];
    new_env[i] = my_strdup(cmd);
    new_env[i + 1] = NULL;
    free(shell->env);
    shell->env = new_env;
    return SUCCESS;
}

static char *build_env_string(char *var, char *value)
{
    int total_len = my_strlen(var) + my_strlen(value) + 2;
    char *result = malloc(sizeof(char) * total_len);

    if (!result)
        return NULL;
    my_strcpy(result, var);
    my_strcat(result, "=");
    my_strcat(result, value);
    return result;
}

static char *build_env_var_single(shell_parameters_t *shell)
{
    char *result = malloc((my_strlen(shell->command[1]) + 2) * sizeof(char));

    if (!result)
        return NULL;
    result[0] = '\0';
    my_strcat(result, shell->command[1]);
    my_strcat(result, "=");
    return result;
}

static void set_error(shell_parameters_t *shell, int code, char *message)
{
    my_putstr_error(message);
    shell->last_exit_code = code;
    shell->command_found = 1;
}

static char *test_len(shell_parameters_t *shell, int cmd_len)
{
    if (cmd_len == 3) {
        if (my_check_if_alphanums(shell->command[1]) == EXIT_FAIL) {
            set_error(shell, 84, "setenv: Variable name must contain "
                "alphanumeric characters.\n");
            return NULL;
        }
        return build_env_string(shell->command[1], shell->command[2]);
    }
    if (cmd_len == 2) {
        if (my_check_if_alphanums(shell->command[1]) == EXIT_FAIL) {
            set_error(shell, 84, "setenv: Variable name must contain "
                "alphanumeric characters.\n");
            return NULL;
        }
        return build_env_var_single(shell);
    }
    set_error(shell, 84, "setenv: too many arguments.\n");
    return NULL;
}

int set_env(shell_parameters_t *shell)
{
    int ret = 0;
    char *env_str = NULL;
    int cmd_len = my_tablen(shell->command);

    env_str = test_len(shell, cmd_len);
    if (env_str == NULL)
        return COMMAND_FOUND;
    if (check_if_env_var_exists(shell, env_str) == EXIT_FAIL)
        ret = create_new_env_var(shell, env_str);
    free(env_str);
    shell->last_exit_code = ret;
    shell->command_found = 1;
    return COMMAND_FOUND;
}
