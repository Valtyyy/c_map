/*
** EPITECH PROJECT, 2026
** map
** File description:
** map_max_size
*/

#include "map.h"
#include <stdint.h>

size_t map_max_size(const map_t *map)
{
    (void)map;
    return SIZE_MAX / sizeof(map_entry_t);
}
