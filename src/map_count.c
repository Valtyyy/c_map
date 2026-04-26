/*
** EPITECH PROJECT, 2026
** map
** File description:
** map_count
*/

#include "map.h"

size_t map_count(const map_t *map, int (*cmp)(const char *key,
    const void *value))
{
    size_t count = 0;
    map_entry_t *entry;

    for (size_t i = 0; i < map->bucket_count; i++)
        for (entry = map->buckets[i]; entry; entry = entry->next)
            if (cmp(entry->key, entry->value))
                count++;
    return count;
}
