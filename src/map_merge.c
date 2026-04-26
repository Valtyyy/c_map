/*
** EPITECH PROJECT, 2026
** map
** File description:
** map_merge
*/

#include "map.h"

void map_merge(map_t *dst, map_t *src)
{
    map_entry_t *entry;

    for (size_t i = 0; i < src->bucket_count; i++) {
        entry = src->buckets[i];
        while (entry) {
            map_insert(dst, entry->key, entry->value);
            entry = entry->next;
        }
    }
}
