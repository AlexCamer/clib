#pragma once

#include "function/compare.h"
#include "utility/types.h"

struct TreeMapNode;

struct TreeMap {
    struct TreeMapNode *root;
    usize key_size;
    usize value_size;
    Compare compare;
};

#define tree_map_empty(map) ((map)->root == NULL)
#define tree_map_contains(map, key) (tree_map_at(map, key) != NULL)
#define tree_map_emplace_cast(map, key, type) ((type *) tree_map_emplace(map, key))
#define tree_map_at_cast(map, key, type) ((type *) tree_map_at(map, key))

void tree_map_construct(struct TreeMap *map, usize key_size, usize value_size, Compare compare);
void tree_map_destruct(struct TreeMap *map);
void *tree_map_emplace(struct TreeMap *map, const void *key);
void tree_map_insert(struct TreeMap *map, const void *key, const void *value);
void tree_map_erase(struct TreeMap *map, const void *key);
void *tree_map_at(const struct TreeMap *map, const void *key);

struct TreeMapIterator {
    struct TreeMap *map;
    struct TreeMapNode *node;
    bool reverse;
};

#define tree_map_iterator_end(it) ((it)->node == NULL)
#define tree_map_iterator_key_cast(it, type) ((type *) tree_map_iterator_key(it))
#define tree_map_iterator_value_cast(it, type) ((type *) tree_map_iterator_value(it))

struct TreeMapIterator tree_map_iterator_begin(struct TreeMap *map);
struct TreeMapIterator tree_map_iterator_rbegin(struct TreeMap *map);
void tree_map_iterator_increment(struct TreeMapIterator *it);
void tree_map_iterator_erase(struct TreeMapIterator *it);
void *tree_map_iterator_key(struct TreeMapIterator *it);
void *tree_map_iterator_value(struct TreeMapIterator *it);
