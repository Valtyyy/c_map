/*
** EPITECH PROJECT, 2026
** map
** File description:
** FNV-1a hash
*/

#include "hash.h"
#include <stdint.h>

size_t hash_bucket(const char *key, size_t bucket_count)
{
    uint64_t hash = 14695981039346656037ULL;

    for (; *key; key++) {
        hash ^= (uint8_t)*key;
        hash *= 1099511628211;
    }
    return (size_t)(hash % bucket_count);
}
