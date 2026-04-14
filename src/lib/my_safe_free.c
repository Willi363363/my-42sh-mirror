/*
** EPITECH PROJECT, 2025
** my_strcpy
** File description:
** Copies a string to another one.
*/
#include "./../../includes/global.h"

void my_safe_free(void **ptr_to_free)
{
    if (ptr_to_free != NULL && (*ptr_to_free) != NULL) {
        free(*ptr_to_free);
        (*ptr_to_free) = NULL;
    }
}
