/*
** EPITECH PROJECT, 2025
** shortcuts.c
** File description:
** This file contains all the shortcuts of the cod editor.
*/
#include "global.h"

void shortcuts_checker(editor_t *editor, file_infos_t *file_infos)
{
    if (editor->typed_ch == CTRL('s')) {
        write_in_file(file_infos, file_infos->filecontent);
        editor->saved = 1;
    }
}
