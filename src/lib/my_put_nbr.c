/*
** EPITECH PROJECT, 2025
** my_put_nbr.c
** File description:
** This script displays the number given as a parameter.
*/
#include "./../../includes/global.h"

int my_put_nbr(int nb)
{
    long n = nb;

    if (n < 0) {
        my_putchar('-');
        n = -n;
    }
    if (n >= 10) {
        my_put_nbr(n / 10);
    }
    my_putchar((n % 10) + '0');
    return 0;
}
