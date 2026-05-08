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

Test(lex_split_words, command_with_quotes)
{
    char **result = lex_split_words("echo \"Hello World\" 'and goodbye'");

    cr_assert_str_eq(result[0], "echo");
    cr_assert_str_eq(result[1], "Hello World");
    cr_assert_str_eq(result[2], "and goodbye");
    cr_assert_null(result[3]);
    word_array_destroy(&result);
}

Test(lex_split_words, command_with_operators)
{
    char **result = lex_split_words("ls -l | grep txt > output.txt");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_str_eq(result[2], "|");
    cr_assert_str_eq(result[3], "grep");
    cr_assert_str_eq(result[4], "txt");
    cr_assert_str_eq(result[5], ">");
    cr_assert_str_eq(result[6], "output.txt");
    cr_assert_null(result[7]);
    word_array_destroy(&result);
}

Test(lex_split_words, command_with_operators_without_spaces)
{
    char **result = lex_split_words("ls -l|grep txt>output.txt");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_str_eq(result[2], "|");
    cr_assert_str_eq(result[3], "grep");
    cr_assert_str_eq(result[4], "txt");
    cr_assert_str_eq(result[5], ">");
    cr_assert_str_eq(result[6], "output.txt");
    cr_assert_null(result[7]);
    word_array_destroy(&result);
}
