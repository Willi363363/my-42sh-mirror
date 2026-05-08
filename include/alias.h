/*
** EPITECH PROJECT, 2026
** alias.h
** File description:
** Alias management header file
*/
#ifndef ALIAS_H
    #define ALIAS_H
    #include <stddef.h>

typedef struct alias_s {
    char *name;
    char **value;
} alias_t;

size_t aliases_len(alias_t *aliases);
int aliases_remove(alias_t **aliases, size_t index);
int aliases_push(alias_t **aliases, char *name, char *value);

#endif /* !ALIAS_H */
