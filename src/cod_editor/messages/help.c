/*
** EPITECH PROJECT, 2025
** help.c
** File description:
** This file contains all the help messages of the cod editor.
*/
#include "global.h"

int editor_help(code)
{
    printf("\n\033[1;32mCOD - Text Editor v%s\033[0m\n\n", VERSION);
    printf("\033[1;35mUSAGE:\033[0m\n");
    printf("  ./cod                 Create new file\n");
    printf("  ./cod <filename>      Open or create file\n");
    printf("  ./cod --help          Display this help\n");
    printf("  ./cod --version       Show version\n\n");
    printf("\033[1;35mKEYBINDS:\033[0m\n");
    printf("  Ctrl + S              Save file\n");
    printf("  Esc                   Quit editor\n\n");
    return code;
}

int display_version_message(code)
{
    printf("------------------------\n");
    printf("Current version : \033[32m%s\033[0m\n", VERSION);
    printf("------------------------\n");
    return code;
}
