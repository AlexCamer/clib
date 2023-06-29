#pragma once

#include "utility/functions.h"
#include "utility/types.h"

struct HashMap {
    byte *data;
    usize size;
    usize capacity;
    usize keySize;
    usize valueSize;
    Hash hash;
    Compare compare;
};

void HashMap_Construct(struct HashMap *map, usize keySize, usize valueSize, Hash hash, Compare compare);
void HashMap_Destruct(struct HashMap *map);
void HashMap_Insert(struct HashMap *map, const void *key, const void *value);
void HashMap_Erase(struct HashMap *map, const void *key);
bool HashMap_Contains(const struct HashMap *map, const void *key);
void *HashMap_At(const struct HashMap *map, const void *key);
