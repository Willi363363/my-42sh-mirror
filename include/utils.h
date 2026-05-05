/*
** EPITECH PROJECT, 2026
** utils.h
** File description:
** Utils header file
*/
#ifndef UTILS_H
    #define UTILS_H

int my_tablen(char **tab);
void safe_free(void **ptr);
int my_putstr_error(char const *str);
int safe_dup2(int fd, int target);
char *my_itoa(int nb);
char **my_str_to_word_array(char *str);
int is_alphanums(char const *str);
char *crop_str_skip(char *str, int chars_to_skip);

#endif /* !UTILS_H */
