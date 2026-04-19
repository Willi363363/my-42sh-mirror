/*
** EPITECH PROJECT, 2026
** G-PSU-200-MPL-2-1-42sh-5
** File description:
** safe_dup2
*/

#include "../includes/global.h"

int safe_dup2(int fd, int target)
{
    if (fd < 0)
        return EXIT_FAIL;
    if (dup2(fd, target) == -1)
        return EXIT_FAIL;
    return SUCCESS;
}
