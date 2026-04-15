/*
** EPITECH PROJECT, 2025
** git_check.c
** File description:
** This file contains all my envs commands functions.
*/
#include "global.h"

static int get_branch(git_detector_t *git_d)
{
    struct stat s;
    int fd = open(git_d->head_path, O_RDONLY);

    if (fd == -1)
        return EXIT_FAIL;
    if (stat(git_d->head_path, &s) == -1)
        return EXIT_FAIL;
    git_d->branch =
        malloc((s.st_size - my_strlen(git_d->head_path) + 1) * sizeof(char));
    if (!(git_d->branch))
        return EXIT_FAIL;
    if (read(fd, git_d->branch + my_strlen(git_d->head_path) +
            1, sizeof(git_d->branch)) == -1) {
        free(git_d->branch);
        return EXIT_FAIL;
    }
    return SUCCESS;
}

int git_check(shell_parameters_t *shell, char *dir_open)
{
    DIR *current = opendir(dir_open);
    struct dirent *new = readdir(current);

    while (new != NULL) {
        if (my_strcmp(".git", new->d_name) == 0 && new->d_type == 4) {
            closedir(current);
            return 1;
        }
        new = readdir(current);
    }
    closedir(current);
    return 0;
}

static int build_next_rewind(char *dir)
{
    char *dir_cpy = my_strdup(dir);
    int found = -1;

    if ((!dir) || (!dir_cpy))
        return EXIT_FAIL;
    for (int i = 0; dir[i] != '\0'; i++)
        if (dir[i] == '/')
            found = i;
    if (found == -1)
        return EXIT_FAIL;
    free(dir);
    dir = malloc(found * sizeof(char));
    for (int i = 0; i < found; i++)
        dir[i] = dir_cpy[i];
    dir[found + 1] = '\0';
    free(dir_cpy);
    return SUCCESS;
}

static int build_head_path(git_detector_t *git_d)
{
    char *head_basic = ".git/HEAD";

    git_d->head_path =
        malloc((my_strlen(git_d->path_to_dgit) +
            my_strlen(head_basic) + 2) * sizeof(char));
    if (!git_d->head_path)
        return EXIT_FAIL;
    git_d->head_path[0] = '\0';
    my_strcat(git_d->head_path, git_d->path_to_dgit);
    my_strcat(git_d->head_path, "/");
    my_strcat(git_d->head_path, head_basic);
    return SUCCESS;
}

static int git_rewind_dirs(shell_parameters_t *shell, git_detector_t *git_d)
{
    while (git_d->dgit_found != 1) {
        if (my_strcmp(git_d->path_to_dgit, shell->home) == 0)
            return 0;
        if (git_check(shell, git_d->path_to_dgit) == 1)
            return 1;
        build_next_rewind(git_d->path_to_dgit);
    }
    return git_d->dgit_found;
}

static int cpy_limit_with_i(char *dest, char const *src, int max, int *i)
{
    for (int j = 0; (*i) < max && src[j] != '\0'; (*i)++) {
        dest[(*i)] = src[j];
        j++;
    }
    dest[(*i)] = '\0';
    return SUCCESS;
}

static int git_free_nleave(git_detector_t *git_d, int with_code)
{
    my_safe_free((void *)&git_d->branch);
    my_safe_free((void *)&git_d->head_path);
    my_safe_free((void *)&git_d->path_to_dgit);
    return with_code;
}

static void draw_git(shell_parameters_t *shell,
    git_detector_t *git_d, char *tempo, int *i)
{
    cpy_limit_with_i(shell->pwd, tempo, MAX_PATH_LEN, i);
    cpy_limit_with_i(shell->pwd, " [git]: (", MAX_PATH_LEN, i);
    cpy_limit_with_i(shell->pwd, git_d->branch, MAX_PATH_LEN, i);
    cpy_limit_with_i(shell->pwd, ")", MAX_PATH_LEN, i);
}

int git_handler(shell_parameters_t *shell)
{
    git_detector_t git_d = {0};
    char *tempo = NULL;
    int i = 0;

    git_d.path_to_dgit = my_strdup(shell->pwd);
    if (!git_d.path_to_dgit)
        return EXIT_FAIL;
    if (git_rewind_dirs(shell, &git_d) == 0)
        return git_free_nleave(&git_d, 0);
    if (build_head_path(&git_d) == EXIT_FAIL)
        return git_free_nleave(&git_d, EXIT_FAIL);
    if (get_branch(&git_d) == EXIT_FAIL)
        return git_free_nleave(&git_d, EXIT_FAIL);
    tempo = my_strdup(shell->pwd);
    if (!tempo)
        return git_free_nleave(&git_d, EXIT_FAIL);
    draw_git(shell, &git_d, tempo, &i);
    free(tempo);
    return git_free_nleave(&git_d, SUCCESS);
}
