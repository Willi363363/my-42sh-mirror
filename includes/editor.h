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
int create_new_file_ask(void);
int window_loop(file_infos_t *file_infos);
void shortcuts_checker(editor_t *editor, file_infos_t *file_infos);
#endif /* EDITOR_H_ */
