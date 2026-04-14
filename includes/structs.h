/*
** EPITECH PROJECT, 2025
** structs.h
** File description:
** Header file for mysh.
*/

#ifndef STRUCTS_H_
    #define STRUCTS_H_
typedef struct shell_parameters_s {
    int status;
    char **env;
    char pwd[MAX_PATH_LEN];
    char *line;
    size_t line_lenght;
    ssize_t nread;
    int last_exit_code;
    int command_found;
    char **paths;
    char **command;
    char *command_real_path;
    char *home;
} shell_parameters_t;
typedef struct git_detector_s {
    char *path_to_dgit;
    int dgit_found;
    char *head_path;
    char *branch;
} git_detector_t;
#endif /* STRUCTS_H_ */
