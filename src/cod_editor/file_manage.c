/*
** EPITECH PROJECT, 2025
** file_manage.c
** File description:
** This file manage input files from the cod editor.
*/
#include "global.h"

int create_new_file(char *name)
{
    char command[512];

    sprintf(command, "touch %s", name);
    if (system(command) == 0)
        return SUCCESS;
    return EXIT_FAIL;
}

void ask_confirm_loop(char *yes_or_no, int *confirm, size_t *name_max_size)
{
    while ((*confirm) == 0) {
        printf("Do you want to create a new file? (y/n) : ");
        getline(&yes_or_no, name_max_size, stdin);
        yes_or_no[strcspn(yes_or_no, "\n")] = '\0';
        printf("\n");
        if (strcmp(yes_or_no, "y") != 0 && strcmp(yes_or_no, "n") != 0) {
            printf("Answer y or n please...\n");
            continue;
        }
        (*confirm) = 1;
    }
}

int create_new_file_ask(void)
{
    char *yes_or_no = malloc(256 * sizeof(char));
    size_t name_max_size = 256;
    int confirm = 0;

    if (!(yes_or_no)) {
        printf("MALLOC FAILED, please try again...");
        exit(EXIT_FAIL);
    }
    ask_confirm_loop(yes_or_no, &confirm, &name_max_size);
    if (strcmp(yes_or_no, "n") == 0) {
        free(yes_or_no);
        return EXIT_FAIL;
    }
    free(yes_or_no);
    return SUCCESS;
}
