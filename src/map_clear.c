/*
** EPITECH PROJECT, 2026
** map
** File description:
** map_clear
*/

#include "map.h"
#include <stdlib.h>

void map_clear(map_t *map)
{
    map_entry_t *entry;
    map_entry_t *next;

    for (size_t i = 0; i < map->bucket_count; i++) {
        entry = map->buckets[i];
        while (entry) {
            next = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = next;
        }
        map->buckets[i] = NULL;
    }
    map->size = 0;
}
