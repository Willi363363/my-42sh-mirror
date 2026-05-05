/*
** EPITECH PROJECT, 2026
** utils.h
** File description:
** Utils header file
*/
#ifndef UTILS_H
    #define UTILS_H
    #include <stddef.h>

int my_tablen(char **tab);
void safe_free(void **ptr);
int my_putstr_error(char const *str);
int safe_dup2(int fd, int target);
char *my_itoa(int nb);
char **my_str_to_word_array(char *str);
int is_alphanums(char const *str);
char *crop_str_skip(char *str, int chars_to_skip);

size_t word_array_len(char **array);
int word_array_insert(char ***array, char *word, size_t index);
int word_array_push(char ***array, char *word);
void word_array_destroy(char ***array);
int word_array_remove(char ***array, size_t index);
char **word_array_duplicate(char **array);

#endif /* !UTILS_H */
