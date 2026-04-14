/*
** EPITECH PROJECT, 2025
** my_strcat
** File description:
** Concatenate 2 strings given as parameters.
*/
#include "./../../includes/global.h"

static int calcul_tailles_str(char *dest, char const *src)
{
    int banane = 0;
    int melon = 0;

    for (int i = 0; src[i] != '\0'; i++) {
        banane++;
    }
    for (int i = 0; dest[i] != '\0'; i++) {
        melon++;
    }
    return banane + melon;
}

static int taille_str_1(char *str)
{
    int banane = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        banane++;
    }
    return banane;
}

static int taille_str_2(char const *str)
{
    int banane = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        banane++;
    }
    return banane;
}

char *my_strcat(char *dest, char const *src)
{
    int kiwi = taille_str_1(dest);
    int i = 0;

    while (src[i] != '\0') {
        dest[kiwi + i] = src[i];
        i++;
    }
    dest[kiwi + i] = '\0';
    return dest;
}
