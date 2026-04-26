/*
** EPITECH PROJECT, 2026
** map
** File description:
** map_find
*/

#include "map.h"

void *map_find(const map_t *map, int (*cmp)(const char *key,
    const void *value))
{
    map_entry_t *entry;

    for (size_t i = 0; i < map->bucket_count; i++) {
        entry = map->buckets[i];
        while (entry) {
            if (cmp(entry->key, entry->value))
                return entry->value;
            entry = entry->next;
        }
    }
    return NULL;
}
