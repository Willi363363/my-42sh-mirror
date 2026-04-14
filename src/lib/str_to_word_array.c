/*
** EPITECH PROJECT, 2025
** str_to_word_array.c
** File description:
** Transform a char * into a word char **.
*/
#include "../../includes/global.h"

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
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '\t')
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
    while (str[(*i)] != ' ' && str[(*i)] != '\0' && str[(*i)] != '\t') {
        (*wsize)++;
        (*i)++;
    }
    return 1;
}

static void copy_word(char **res, int res_i, char *src, int wsize)
{
    int a = 0;

    res[res_i] = malloc((wsize + 1) * sizeof(char));
    while (a < wsize) {
        res[res_i][a] = src[a];
        a++;
    }
    res[res_i][wsize] = '\0';
}

static int process_word(char *str, int i, int *start, int *wsize)
{
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

static void array_builder(char *str, int i, char **res, int res_i)
{
    int wsize = 0;
    int start_pos = 0;

    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '\0')
        return;
    i = process_word(str, i, &start_pos, &wsize);
    copy_word(res, res_i, str + start_pos, wsize);
    while (str[i] == ' ')
        i++;
    array_builder(str, i, res, res_i + 1);
}

char **my_str_to_word_array(char *str)
{
    int count = 0;
    char **result = NULL;

    if (str == NULL)
        return NULL;
    count = words_counter(str, 0);
    if (count == 0)
        return NULL;
    result = malloc((count + 1) * sizeof(char *));
    result[count] = NULL;
    if (!result)
        return NULL;
    array_builder(str, 0, result, 0);
    return result;
}
