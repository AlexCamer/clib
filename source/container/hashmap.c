#include "container/hashmap.h"
#include "utility/macros.h"

#define HASH_MAP_MIN_CAPACITY_LOG2 6
#define HASH_MAP_MIN_CAPACITY EXP2(HASH_MAP_MIN_CAPACITY_LOG2)
#define HASH_MAP_MIN_LOAD_FACTOR 0.1
#define HASH_MAP_MAX_LOAD_FACTOR 0.6

struct HashMapBucket {
    u32 distance;
};

void hash_map_construct(struct HashMap *map, usize key_size, usize value_size, Hash hash, Compare compare) {
    map->size = 0;
    map->capacity = HASH_MAP_MIN_CAPACITY;
    map->key_size = key_size;
    map->value_size = value_size;
    map->bucket_size = sizeof(struct HashMapBucket) + PAD_EXP2(key_size, 2) + PAD_EXP2(value_size, 2);
    map->hash = hash;
    map->compare = compare;
}

void hash_map_destruct(struct HashMap *map) {
    xfree(map->data);
}

void hash_map_insert(struct HashMap *map, const void *key, const void *value);

void hash_map_erase(struct HashMap *map, const void *key);

bool hash_map_contains(const struct HashMap *map, const void *key);

void *hash_map_at(const struct HashMap *map, const void *key);
