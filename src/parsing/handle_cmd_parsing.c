/*
** EPITECH PROJECT, 2026
** handle_cmd_parsing.c
** File description:
** Handle command parsing and execution
*/
#include "execution.h"
#include "global.h"
#include "history.h"
#include "lexer.h"
#include "parsing.h"

int handle_cmd_parsing(shell_parameters_t *shell)
{
    int found = 0;
    int result = 0;
    ast_node_t *ast = NULL;
    lexer_t **lexer = lexer_tokenize(shell);

    if (!lexer)
        return EXIT_FAIL;
    found = ast_create(&ast, lexer);
    ast_expand_env(ast, shell);
    result = run_ast(ast, shell);
    push_to_history(shell);
    lexer_destroy(lexer);
    ast_destroy(ast);
    if (found != SUCCESS)
        return found;
    else
        return result;
}
