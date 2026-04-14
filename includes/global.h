/*
** EPITECH PROJECT, 2025
** global.h
** File description:
** Header file for mysh.
*/

#ifndef GLOBAL_H_
    #define GLOBAL_H_
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <signal.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <sys/time.h>
    #include <sys/resource.h>
    #include <errno.h>
    #include <ncurses.h>
    #define MAX_PATH_LEN 4096
    #include "structs.h"
    #include "parsing.h"
    #include "prototypes.h"
    #include "editor.h"
    #define SUCCESS 0
    #define EXIT_FAIL 84
    #define RUNNING 1
    #define COMMAND_FOUND 3
    #define COMMAND_ERROR -3
    #define NOT_FOUND 404
#endif /* GLOBAL_H_ */
