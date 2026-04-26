/*
** EPITECH PROJECT, 2026
** map
** File description:
** map_erase
*/

#include "map.h"
#include <stdlib.h>

int map_erase(map_t *map, size_t index)
{
    size_t current = 0;
    map_entry_t **prev;
    map_entry_t *entry;

    for (size_t i = 0; i < map->bucket_count; i++) {
        prev = &map->buckets[i];
        entry = map->buckets[i];
        while (entry) {
            if (current == index) {
                *prev = entry->next;
                free(entry->key);
                free(entry->value);
                free(entry);
                map->size--;
                return 0;
            }
            current++;
            prev = &entry->next;
            entry = entry->next;
        }
    }
    return -1;
}
