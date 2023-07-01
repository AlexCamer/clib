#pragma once

#include "function/compare.h"
#include "function/hash.h"
#include "utility/types.h"

struct HashMap {
    byte *data;
    usize size;
    usize capacity;
    usize key_size;
    usize value_size;
    usize bucket_size;
    Hash hash;
    Compare compare;
};

void hash_map_construct(struct HashMap *map, usize key_size, usize value_size, Hash hash, Compare compare);
void hash_map_destruct(struct HashMap *map);
void hash_map_insert(struct HashMap *map, const void *key, const void *value);
void hash_map_erase(struct HashMap *map, const void *key);
bool hash_map_contains(const struct HashMap *map, const void *key);
void *hash_map_at(const struct HashMap *map, const void *key);
