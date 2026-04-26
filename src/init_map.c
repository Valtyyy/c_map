/*
** EPITECH PROJECT, 2026
** map
** File description:
** init_map
*/

#include "map.h"
#include <stdlib.h>

map_t init_map(size_t child_size)
{
    map_t map = {0};

    map.child_size = child_size;
    map.bucket_count = MAP_BUCKET_COUNT;
    map.buckets = calloc(MAP_BUCKET_COUNT, sizeof(map_entry_t *));
    return map;
}
