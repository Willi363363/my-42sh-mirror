/*
** EPITECH PROJECT, 2026
** safe_free.c
** File description:
** Free a pointer and set it to NULL
*/
#include <stdlib.h>
#include "utils.h"

void safe_free(void **ptr)
{
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}
