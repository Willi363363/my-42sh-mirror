/*
** EPITECH PROJECT, 2026
** handle_signal.c
** File description:
** Handle a signal and return the corresponding exit code
*/
#include <string.h>
#include <sys/wait.h>
#include "execution.h"
#include "utils.h"

int handle_signal(int status)
{
    int sig = 0;

    if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        if (sig == SIGFPE)
            my_putstr_error("Floating exception");
        else
            my_putstr_error(strsignal(sig));
#ifdef WCOREDUMP
        if (WCOREDUMP(status))
            my_putstr_error(" (core dumped)");
#endif
        my_putstr_error("\n");
    }
    return 128 + sig;
}
