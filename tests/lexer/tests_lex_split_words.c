/*
** EPITECH PROJECT, 2026
** tests_lex_split_words.c
** File description:
** This file contains unit tests for the lex_split_words function
*/
#include <criterion/criterion.h>
#include "lexer.h"
#include "utils.h"

Test(lex_split_words, simple_command)
{
    char **result = lex_split_words("ls -l /home");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_str_eq(result[2], "/home");
    cr_assert_null(result[3]);
    word_array_destroy(&result);
}
