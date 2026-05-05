/*
** EPITECH PROJECT, 2025
** ast.h
** File description:
** AST struct definition
*/

#ifndef AST_H_
    #define AST_H_
    #include "lexer.h"
    #include <stddef.h>

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

ast_node_t *ast_node_create(void);
int ast_create(ast_node_t **ast, lexer_t **tokens);
ast_node_t *ast_create_rec(size_t *pos, lexer_t **lexer);
void ast_expand_env(ast_node_t *node, shell_parameters_t *shell);
void ast_destroy(ast_node_t *ast);
int handle_cmd_parsing(shell_parameters_t *shell);

#endif /* AST_H_ */
