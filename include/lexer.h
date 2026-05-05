/*
** EPITECH PROJECT, 2026
** lexer.h
** File description:
** Lexer header file
*/
#ifndef LEXER_H
    #define LEXER_H
    #include "shell.h"
    #define MAX_ARG_LEN 1024

typedef enum {
    TOKEN_WORD,
    TOKEN_ENV_VAR,
    TOKEN_PIPE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_SEMICOLON,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_HEREDOC,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF
} lexer_id_t;

typedef struct lexer_s {
    lexer_id_t type;
    char *value;
} lexer_t;

void lexer_destroy(lexer_t **nodes);
lexer_t **lexer_tokenize(shell_parameters_t *shell);

int count_words(char *str);
int lex_operators(char *str, int *i);
int build_word_array(char *str, char **res);
int process_word(char *str, int i, int *start, int *wsize);
char **lex_split_words(shell_parameters_t *shell);

#endif /* !LEXER_H */
