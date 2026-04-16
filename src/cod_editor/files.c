/*
** EPITECH PROJECT, 2025
** launch.c
** File description:
** This file launch the cod editor.
*/
#include "global.h"

int check_if_file_is_here(file_infos_t *file_infos)
{
    if (stat(file_infos->filepath, file_infos->file_stat) == EXIT_FAIL)
        return EXIT_FAIL;
    file_infos->fd = open(file_infos->filepath, O_RDONLY);
    if (file_infos->fd == -1)
        return EXIT_FAIL;
    return SUCCESS;
}

int read_the_file(file_infos_t *file_infos)
{
    file_infos->filecontent =
        malloc((file_infos->file_stat->st_size + 1) * sizeof(char));
    if (read(file_infos->fd, file_infos->filecontent,
            file_infos->file_stat->st_size) == EXIT_FAIL)
        return EXIT_FAIL;
    file_infos->filecontent[file_infos->file_stat->st_size] = '\0';
    return SUCCESS;
}

void free_it(file_infos_t *file_infos)
{
    if (file_infos->filecontent)
        free(file_infos->filecontent);
    if (file_infos->filepath)
        free(file_infos->filepath);
    if (file_infos->fd > 0)
        close(file_infos->fd);
}

void fill_new_file_infos(char *name, file_infos_t *file_infos)
{
    file_infos->filepath = my_strdup(name);
}
