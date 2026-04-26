/*
** EPITECH PROJECT, 2026
** map
** File description:
** map_insert
*/

#include "map.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>

int map_insert(map_t *map, const char *key, const void *value)
{
    size_t idx = hash_bucket(key, map->bucket_count);
    map_entry_t *entry = map->buckets[idx];
    map_entry_t *new_entry;

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            memcpy(entry->value, value, map->child_size);
            return 0;
        }
        entry = entry->next;
    }
    new_entry = malloc(sizeof(map_entry_t));
    if (!new_entry)
        return -1;
    new_entry->key = strdup(key);
    new_entry->value = malloc(map->child_size);
    if (!new_entry->key || !new_entry->value) {
        free(new_entry->key);
        free(new_entry->value);
        free(new_entry);
        return -1;
    }
    memcpy(new_entry->value, value, map->child_size);
    new_entry->next = map->buckets[idx];
    map->buckets[idx] = new_entry;
    map->size++;
    return 0;
}
