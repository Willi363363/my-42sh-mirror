/*
** EPITECH PROJECT, 2025
** global.h
** File description:
** Header file for mysh.
*/

#ifndef PARSING_H_
    #define PARSING_H_
typedef enum {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_AND,
    NODE_OR,
    NODE_SEQUENCE,
    NODE_SUBSHELL,
    NODE_REDIR_IN,
    NODE_REDIR_HEREDOC,
    NODE_REDIR_OUT,
    NODE_REDIR_APPEND
} nodetype_t;

typedef struct ast_node_s {
    nodetype_t type;
    char **args;
    char *input_file;
    char *output_file;
    int append_mode;
    struct ast_node_s *left;
    struct ast_node_s *right;
    struct ast_node_s *payload;
} ast_node_t;

typedef enum {
    TOKEN_WORD,
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
#endif /* PARSING_H_ */
