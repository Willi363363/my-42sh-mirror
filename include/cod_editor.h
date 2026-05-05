/*
** EPITECH PROJECT, 2025
** cod_editor.h
** File description:
** Cod editor header file
*/

#ifndef COD_EDITOR_H_
    #define COD_EDITOR_H_
    #define VERSION "0.1.0"
    #define CTRL(c) ((c) & 0x1F)
    #include <sys/stat.h>
    #include "shell.h"

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

int launch_cod_editor(shell_parameters_t *shell);
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

#endif /* COD_EDITOR_H_ */
