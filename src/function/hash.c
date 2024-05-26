#include "function/hash.h"

u64 hash_x32(const void *key) {
    u64 hash = (u64) *((u32 *) key);
    hash += ~(hash << 15);
    hash ^= (hash >> 10);
    hash += (hash << 3);
    hash ^= (hash >> 6);
    hash += ~(hash << 11);
    hash ^= (hash >> 16);
    return hash;
}

u64 hash_x64(const void *key) {
    u64 hash = (u64) *((u64 *) key);
    hash += ~(hash << 32);
    hash ^= (hash >> 22);
    hash += ~(hash << 13);
    hash ^= (hash >> 8);
    hash += (hash << 3);
    hash ^= (hash >> 15);
    hash += ~(hash << 27);
    hash ^= (hash >> 31);
    return hash;
}
