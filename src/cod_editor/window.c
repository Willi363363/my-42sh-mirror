/*
** EPITECH PROJECT, 2025
** launch.c
** File description:
** This file launch the cod editor.
*/
#include "global.h"

void write_in_file(file_infos_t *file_infos, char *new_content)
{
    file_infos->fd = open(file_infos->filepath, O_WRONLY | O_TRUNC);
    write(file_infos->fd, new_content, strlen(new_content));
    ftruncate(file_infos->fd, strlen(new_content));
    close(file_infos->fd);
}

static void draw_header(file_infos_t *file_infos)
{
    clear();
    printw("\n");
    printw("                         /`·.¸          \n");
    printw("                        /¸...¸`:·       \n");
    printw("   ---              ¸.·´  ¸   `·.¸.·´)  \n");
    printw(" | cod |          : © ):´;      ¸  {    \n");
    printw("   ----            `·.¸ `·  ¸.·´\\`·¸)  \n");
    printw("                        `\\\\´´\\¸.·´       ");
    printw("current version : %s\n\n", VERSION);
    printw("%s", file_infos->filecontent);
}

static void saved_status(editor_t *editor)
{
    if (editor->saved == 1)
        mvprintw(LINES - 1, COLS - 20, "STATUS : SAVED");
    else
        mvprintw(LINES - 1, COLS - 20, "STATUS : NOT SAVED");
    move(editor->cursor_y, editor->cursor_x);
    refresh();
    editor->typed_ch = getch();
    if (editor->typed_ch == 27 && editor->saved == 0) {
        mvprintw(LINES - 1, 0, "Quit without saving : y/n");
        refresh();
        if (getch() == 'y') {
            editor->is_running = 0;
        }
    } else if (editor->typed_ch == 27 && editor->saved == 1) {
        editor->is_running = 0;
    }
}

static void chars_watcher(editor_t *editor, file_infos_t *file_infos)
{
    if (editor->typed_ch >= 32 && editor->typed_ch <= 126 || editor->typed_ch == '\t' || editor->typed_ch == '\n') {
        editor->len = strlen(file_infos->filecontent);
        editor->tempo_realloc_test = realloc(file_infos->filecontent, editor->len + 2);
        if (editor->tempo_realloc_test == NULL) {
            endwin();
            printf("REALLOC FAILED, try again...");
            exit(EXIT_FAIL);
        } else
            file_infos->filecontent = editor->tempo_realloc_test;
        file_infos->filecontent[editor->len] = (char)editor->typed_ch;
        file_infos->filecontent[editor->len + 1] = '\0';
        editor->saved = 0;
    }
}

static void delete(editor_t *editor, file_infos_t *file_infos)
{
    editor->len = strlen(file_infos->filecontent);
    if (editor->len > 0) {
        editor->tempo_realloc_test = realloc(file_infos->filecontent, editor->len);
        if (editor->tempo_realloc_test == NULL) {
            endwin();
            printf("REALLOC FAILED, try again...");
            exit(EXIT_FAIL);
        } else
            file_infos->filecontent = editor->tempo_realloc_test;
        file_infos->filecontent[editor->len - 1] = '\0';
        editor->saved = 0;
    }
}

int window_loop(file_infos_t *file_infos)
{
    editor_t editor = {1, 0, 0, NULL, 1, 0, 0, 0};

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    while (editor.is_running == 1) {
        draw_header(file_infos);
        getyx(stdscr, editor.cursor_y, editor.cursor_x);
        saved_status(&editor);
        shortcuts_checker(&editor, file_infos);
        chars_watcher(&editor, file_infos);
        if (editor.typed_ch == KEY_BACKSPACE || editor.typed_ch == 127 || editor.typed_ch == 8)
            delete(&editor, file_infos);
    }
    endwin();
    return SUCCESS;
}
