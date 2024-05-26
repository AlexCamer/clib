#pragma once

#include "container/array.h"
#include "function/compare.h"
#include "function/hash.h"

struct Map {
    struct Array buckets;
    usize size;
    usize key_size;
    usize element_size;
    Hash hash;
    Compare compare;
};

void map_construct(struct Map *map, usize key_size, usize element_size, Hash hash, Compare compare);
void map_destruct(struct Map *map);
void *map_get(const struct Map *map, const void *key);
void *map_add(struct Map *map, const void *key);
void map_remove(struct Map *map, const void *key);
bool map_contains(const struct Map *map, const void *key);
bool map_empty(const struct Map *map);
