/*
** EPITECH PROJECT, 2025
** prototypes.h
** File description:
** Header file for mysh.
*/

#ifndef PROTOTYPES_H_
    #define PROTOTYPES_H_
char **my_str_to_word_array(char *str);
int my_strlen(char const *str);
char *my_strdup(char const *src);
char *my_strcpy(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_putstr(char const *str);
int my_putchar(char c);
int my_put_nbr(int nb);
char *my_strcat(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int len);
char *get_pwd(char **env);
char *crop_str_skip(char *str, int chars_to_skip);
int my_strcmp_skip(char const *skip_here, char const *s2, int chars_to_skip);
int compare_pwd(char **env, shell_parameters_t *shell);
char **duplicate_env(char **env);
int env_cmds_assert(char *line, shell_parameters_t *shell);
int assert_sys_cmd(shell_parameters_t *shell);
void create_paths(shell_parameters_t *shell);
void free_paths(shell_parameters_t *shell);
void clean_every_iteration(shell_parameters_t *shell);
int clean_and_exit(shell_parameters_t *shell);
int my_replace_char(char *str, char to_replace, char replacer);
int misc_cmds_assert(char *line, shell_parameters_t *shell);
char *my_str_remove_char(char const *src, char to_remove);
int my_str_count_char(char const *src, char c);
void my_safe_free(void **ptr_to_free);
int set_env(shell_parameters_t *shell);
int my_tablen(char **tab);
int dir_cmds_assert(char *line, shell_parameters_t *shell);
char *my_strdup_skip_chars(char const *src, int to_skip);
int backup_old_pwd(shell_parameters_t *shell);
int backup_old_pwd_with(shell_parameters_t *shell, char *with);
int unset_env(shell_parameters_t *shell);
int my_putstr_error(char const *str);
int own_cmds_assert(shell_parameters_t *shell);
int signals_interpreter(int status);
int my_check_if_alphanums(char const *str);
int my_strcpy_limit(char *dest, char const *src, int max);
int git_handler(shell_parameters_t *shell);
int execute_ast(shell_parameters_t *shell);
void free_lexer(lexer_t **lexer);
void free_ast(ast_node_t *ast);
lexer_t **apply_lexer(shell_parameters_t *shell);
char **tokenize_formatter(shell_parameters_t *shell);
int detect_operators(char *str, int *i);
ast_node_t *parse_list(int *pos, lexer_t **lexer);
int run_ast(ast_node_t *node, shell_parameters_t *shell);
int exec_command(ast_node_t *node, shell_parameters_t *shell);
int exec_pipe(ast_node_t *node, shell_parameters_t *shell);
int exec_and(ast_node_t *node, shell_parameters_t *shell);
int exec_or(ast_node_t *node, shell_parameters_t *shell);
int exec_sequence(ast_node_t *node, shell_parameters_t *shell);
int exec_subshell(ast_node_t *node, shell_parameters_t *shell);
int exec_redir_in(ast_node_t *node, shell_parameters_t *shell);
int exec_redir_heredoc(ast_node_t *node, shell_parameters_t *shell);
int exec_redir_out(ast_node_t *node, shell_parameters_t *shell);
int exec_redir_append(ast_node_t *node, shell_parameters_t *shell);
int commands_launcher(shell_parameters_t *shell);
int redir_errors(ast_node_t *node, shell_parameters_t *shell);
int redir_path_error(void);
int heredoc_pipe_error(int *fd);
int cod(shell_parameters_t *shell);
void push_to_history(shell_parameters_t *shell);
char *my_itoa(int nb);
#endif /* PROTOTYPES_H_ */
