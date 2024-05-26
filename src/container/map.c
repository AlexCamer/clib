#include "container/map.h"
#include "utility/memory.h"
#include "utility/macros.h"
#include <string.h>

#define MAP_MIN_CAPACITY_LOG_2 6
#define MAP_MIN_CAPACITY EXP_2(MAP_MIN_CAPACITY_LOG_2)
#define MAP_MAX_LOAD_FACTOR 0.5

struct MapBucketMeta {
    bool full:1;
    u64 hash:63;
};

struct MapBucket {
    struct MapBucketMeta *meta;
    void *key;
    void *element;
    usize index;
    usize distance;
};

struct MapProbeResult {
    struct MapBucket bucket;
    bool found:1;
    u64 hash:63;
};

static inline usize
map_mod(const struct Map *map, u64 hash) {
    usize capacity = map->buckets.size;
    return hash & (capacity - 1);
}

static inline void
map_bucket_get(const struct Map *map, struct MapBucket *bucket, usize index) {
    usize capacity = map->buckets.size;
    assert(index < capacity);
    bucket->meta = array_get(&(map->buckets), index);
    bucket->key = bucket->meta + 1;
    bucket->element = ((byte *) bucket->key) + map->key_size;
    bucket->index = index;
    if (bucket->meta->full == true) {
        usize ideal = map_mod(map, bucket->meta->hash);
        bucket->distance = map_mod(map, index + capacity - ideal);
    }
}

static inline void
map_bucket_next(const struct Map *map, struct MapBucket *bucket) {
    usize next = map_mod(map, bucket->index + 1);
    map_bucket_get(map, bucket, next);
}

static inline void
map_bucket_copy(struct Map *map, struct MapBucket *from, struct MapBucket *to) {
    usize bucket_size = map->buckets.element_size;
    memcpy(from->meta, to->meta, bucket_size);
}

static void
map_probe(const struct Map *map, const void *key, struct MapProbeResult *result) {
    result->hash = map->hash(key);
    struct MapBucket *current = &(result->bucket);
    usize ideal = map_mod(map, result->hash);
    map_bucket_get(map, current, ideal);
    for (usize distance = 0;; distance++) {
        if (current->meta->full == false) {
            result->found = false;
            return;
        }
        if (current->meta->hash == result->hash && map->compare(current->key, key) == 0) {
            result->found = true;
            return;
        }
        if (current->distance < distance) {
            result->found = false;
            return;
        }
        map_bucket_next(map, current);
    }
}

static void
map_shift_up(struct Map *map, struct MapBucket *bucket) {
    struct MapBucket current = *bucket;
    for (usize distance = bucket->distance + 1;; distance++) {
        map_bucket_next(map, &current);
        if (current.meta->full == false) {
            break;
        }
        if (current.distance < distance) {
            map_shift_up(map, &current);
            break;
        }
    }
    map_bucket_copy(map, bucket, &current);
    bucket->meta->full = false;
}

static void
map_shift_down(struct Map *map, struct MapBucket *bucket) {
    bucket->meta->full = false;
    struct MapBucket current = *bucket;
    map_bucket_next(map, &current);
    if (current.meta->full == false || current.distance == 0) {
        return;
    }
    for (;;) {
        struct MapBucket prev = current;
        map_bucket_next(map, &current);
        if (current.meta->full == false || current.distance <= prev.distance) {
            map_bucket_copy(map, &prev, bucket);
            map_shift_down(map, &prev);
            return;
        }
    }
}

static void
map_rehash(struct Map *map) {
    usize old_capacity = map->buckets.size;
    usize new_capacity = MUL2(old_capacity);
    array_resize(&(map->buckets), new_capacity);
    // unfinished
}

void
map_construct(struct Map *map, usize key_size, usize element_size, Hash hash, Compare compare) {
    usize bucket_size = sizeof(struct MapBucketMeta) + key_size + element_size;
    array_construct(&(map->buckets), MAP_MIN_CAPACITY, bucket_size, true);
    map->size = 0;
    map->key_size = key_size;
    map->element_size = element_size;
    map->hash = hash;
    map->compare = compare;
}

void
map_destruct(struct Map *map) {
    array_destruct(&(map->buckets));
}

void *
map_get(const struct Map *map, const void *key) {
    struct MapProbeResult result;
    map_probe(map, key, &result);
    assert(result.found == true);
    return result.bucket.element;
}

void *
map_add(struct Map *map, const void *key) {
    usize capacity = map->buckets.size;
    f32 threshold = MAP_MAX_LOAD_FACTOR * capacity;
    if (map->size > threshold) {
        map_rehash(map);
    }
    struct MapProbeResult result;
    map_probe(map, key, &result);
    struct MapBucket *bucket = &(result.bucket);
    if (result.found == false) {
        struct MapBucketMeta *meta = bucket->meta;
        if (meta->full == true) {
            map_shift_up(map, bucket);
        }
        meta->full = true;
        meta->hash = result.hash;
        memcpy(bucket->key, key, map->key_size);
        map->size++;
    }
    return bucket->element;
}

void
map_remove(struct Map *map, const void *key) {
    struct MapProbeResult result;
    map_probe(map, key, &result);
    assert(result.found == true);
    map_shift_down(map, &(result.bucket));
    map->size--;
}

bool
map_contains(const struct Map *map, const void *key) {
    struct MapProbeResult result;
    map_probe(map, key, &result);
    return result.found;
}

bool
map_empty(const struct Map *map) {
    return map->size == 0;
}
