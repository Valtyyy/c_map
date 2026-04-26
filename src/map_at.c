/*
** EPITECH PROJECT, 2026
** map
** File description:
** map_at
*/

#include "map.h"
#include "hash.h"
#include <string.h>

void *map_at(const map_t *map, const char *key)
{
    size_t idx = hash_bucket(key, map->bucket_count);
    map_entry_t *entry = map->buckets[idx];

    while (entry) {
        if (strcmp(entry->key, key) == 0)
            return entry->value;
        entry = entry->next;
    }
    return NULL;
}
