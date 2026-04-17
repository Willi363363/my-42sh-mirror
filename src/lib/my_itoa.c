/*
** EPITECH PROJECT, 2025
** my_put_nbr.c
** File description:
** This script displays in lower cases the entire alphabet on a single line.
*/
#include "global.h"

static char *create_str(int size, int is_negative, char **str, int nbr)
{
    for (int i = size + is_negative - 1; i >= is_negative; i--) {
        (*str)[i] = (nbr % 10) + '0';
        nbr = nbr / 10;
    }
    (*str)[size + is_negative] = '\0';
    return (*str);
}

static void check_negative(int *nb, int *nbr, int *is_negative)
{
    if ((*nb) < 0) {
        (*is_negative) = 1;
        (*nbr) = -(*nbr);
    }
}

static void process_nb(int *nbr, int *size)
{
    (*nbr) = (*nbr) / 10;
    (*size)++;
}

char *nb_to_str(int nb)
{
    char *str;
    int size = 0;
    int nbr = nb;
    int is_negative = 0;

    check_negative(&nb, &nbr, &is_negative);
    if (nb == 0)
        size = 1;
    else {
        while (nbr > 0) {
            process_nb(&nbr, &size);
        }
    }
    str = malloc((size + is_negative + 1) * sizeof(char));
    if (!str)
        return NULL;
    if (is_negative)
        str[0] = '-';
    nbr = (nb < 0) ? -nb : nb;
    return create_str(size, is_negative, &str, nbr);
}
