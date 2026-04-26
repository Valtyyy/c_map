/*
** EPITECH PROJECT, 2026
** map
** File description:
** map_swap
*/

#include "map.h"

void map_swap(map_t *a, map_t *b)
{
    map_t tmp = *a;

    *a = *b;
    *b = tmp;
}
