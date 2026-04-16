/*
** EPITECH PROJECT, 2025
** structs.h
** File description:
** Header file for mysh.
*/

#ifndef EDITOR_H_
    #define EDITOR_H_
    #define VERSION "0.1.0"
    #define CTRL(c) ((c) & 0x1F)
typedef struct file_infos_s {
    struct stat *file_stat;
    char *filepath;
    char *filecontent;
    int fd;
} file_infos_t;
typedef struct editor_s {
    int is_running;
    int typed_ch;
    int len;
    char *tempo_realloc_test;
    int saved;
    int cursor_x;
    int cursor_y;
    int current_index;
} editor_t;
int editor_help(int code);
int editor_version(int code);
int check_if_file_is_here(file_infos_t *file_infos);
int read_the_file(file_infos_t *file_infos);
void free_it(file_infos_t *file_infos);
char *ask_for_name(void);
int create_new_file(char *name);
int create_new_file_ask(void);
void fill_new_file_infos(char *name, file_infos_t *file_infos);
int window_loop(file_infos_t *file_infos);
void shortcuts_checker(editor_t *editor, file_infos_t *file_infos);
void write_in_file(file_infos_t *file_infos, char *new_content);
#endif /* EDITOR_H_ */
