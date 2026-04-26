/*
** EPITECH PROJECT, 2026
** map
** File description:
** header for export
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>

#define MAP_BUCKET_COUNT 256

typedef struct map_entry_s {
    char *key;
    void *value;
    struct map_entry_s *next;
} map_entry_t;

typedef struct {
    size_t size;
    size_t child_size;
    size_t bucket_count;
    map_entry_t **buckets;
} map_t;

map_t init_map(size_t child_size);
int map_insert(map_t *map, const char *key, const void *value);
void *map_at(const map_t *map, const char *key);
int map_erase(map_t *map, size_t index);
size_t map_size(const map_t *map);
bool map_empty(const map_t *map);
size_t map_max_size(const map_t *map);
void map_swap(map_t *a, map_t *b);
void map_merge(map_t *dst, map_t *src);
void *map_find(const map_t *map, int (*cmp)(const char *key,
    const void *value));
size_t map_count(const map_t *map, int (*cmp)(const char *key,
    const void *value));
void map_clear(map_t *map);
