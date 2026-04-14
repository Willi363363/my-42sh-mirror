/*
** EPITECH PROJECT, 2025
** dir_functions.c
** File description:
** This file contains all my directories commands functions.
*/
#include "../../../includes/global.h"

int backup_old_pwd(shell_parameters_t *shell)
{
    char *oldwdequal = "OLDPWD=";
    char *final_oldwd = NULL;

    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], "OLDPWD=", 7) == 0) {
            my_safe_free((void *)&shell->env[i]);
            final_oldwd = malloc((my_strlen(oldwdequal)
                    + 1 + my_strlen(shell->pwd)) * sizeof(char));
            final_oldwd[0] = '\0';
            my_strcat(final_oldwd, oldwdequal);
            my_strcat(final_oldwd, shell->pwd);
            shell->env[i] = my_strdup(final_oldwd);
            free(final_oldwd);
            return SUCCESS;
        }
    }
    return EXIT_FAIL;
}

int backup_old_pwd_with(shell_parameters_t *shell, char *with)
{
    char *oldwdequal = "OLDPWD=";
    char *final_oldwd = NULL;

    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], "OLDPWD=", 7) == 0) {
            my_safe_free((void *)&shell->env[i]);
            final_oldwd = malloc((my_strlen(oldwdequal)
                    + 1 + my_strlen(with)) * sizeof(char));
            final_oldwd[0] = '\0';
            my_strcat(final_oldwd, oldwdequal);
            my_strcat(final_oldwd, with);
            shell->env[i] = my_strdup(final_oldwd);
            free(final_oldwd);
            return SUCCESS;
        }
    }
    return EXIT_FAIL;
}
