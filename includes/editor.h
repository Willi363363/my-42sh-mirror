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
int editor_help(int code);
int editor_version(int code);
int create_new_file_ask(void);
#endif /* EDITOR_H_ */
