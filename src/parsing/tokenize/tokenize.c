/*
** EPITECH PROJECT, 2025
** str_to_word_array.c
** File description:
** Transform a char * into a word char **.
*/
#include "../includes/global.h"

static int skip_quoted_word(char *str, int i)
{
    i++;
    while (str[i] != '"' && str[i] != '\0')
        i++;
    if (str[i] == '"')
        i++;
    return i;
}

static int skip_normal_word(char *str, int i)
{
    int res = detect_operators(str, &i);

    if (res != 0)
        return i + res;
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '\t'
        && detect_operators(str, &i) == 0)
        i++;
    return i;
}

static int words_counter(char *str, int i)
{
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '\0')
        return 0;
    if (str[i] == '"')
        i = skip_quoted_word(str, i);
    else
        i = skip_normal_word(str, i);
    while (str[i] == ' ')
        i++;
    return 1 + words_counter(str, i);
}

static int detect_if_quoted(char *str, int *i, int *wsize)
{
    while (str[(*i)] != '"' && str[(*i)] != '\0') {
        (*wsize)++;
        (*i)++;
    }
    if (str[(*i)] == '"')
        (*i)++;
    return 1;
}

static int detect_normal(char *str, int *i, int *wsize)
{
    int res = detect_operators(str, i);

    if (res != 0) {
        *wsize = res;
        return 1;
    }
    while (str[(*i)] != ' ' && str[(*i)] != '\0' && str[(*i)] != '\t'
        && detect_operators(str, i) == 0) {
        (*wsize)++;
        (*i)++;
    }
    return 1;
}

static char *copy_word(char *src, int start_pos, int wsize)
{
    char *word = malloc((wsize + 1) * sizeof(char));
    int a = 0;

    if (word == NULL)
        return NULL;
    while (a < wsize) {
        word[a] = src[start_pos + a];
        a++;
    }
    word[wsize] = '\0';
    return word;
}

static int process_word(char *str, int i, int *start, int *wsize)
{
    int op_res = detect_operators(str, &i);

    if (op_res != 0) {
        (*start) = i;
        (*wsize) = op_res;
        return i + op_res;
    }
    if (str[i] == '"') {
        (*start) = i + 1;
        i++;
        detect_if_quoted(str, &i, wsize);
    } else {
        (*start) = i;
        detect_normal(str, &i, wsize);
    }
    return i;
}

static void free_word_array(char **res, int filled)
{
    for (int i = 0; i < filled; i++)
        free(res[i]);
    free(res);
}

static int array_builder(char *str, char **res)
{
    int i = 0;
    int res_i = 0;
    int wsize = 0;
    int start_pos = 0;

    while (str[i] != '\0') {
        wsize = 0;
        for (; str[i] == ' ' || str[i] == '\t'; i++);
        if (str[i] == '\0')
            break;
        i = process_word(str, i, &start_pos, &wsize);
        res[res_i] = copy_word(str, start_pos, wsize);
        if (res[res_i] == NULL) {
            free_word_array(res, res_i);
            return 0;
        }
        res_i++;
    }
    return 1;
}

char **tokenize_formatter(shell_parameters_t *shell)
{
    int count = 0;
    char **result = NULL;

    if (shell == NULL || shell->line == NULL)
        return NULL;
    count = words_counter(shell->line, 0);
    if (count == 0)
        return NULL;
    result = calloc((count + 1), sizeof(char *));
    if (result == NULL)
        return NULL;
    if (!array_builder(shell->line, result))
        return NULL;
    return result;
}
