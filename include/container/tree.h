#pragma once

#include "function/compare.h"
#include "utility/types.h"

struct TreeNode;

struct Tree {
    struct TreeNode *root;
    usize key_size;
    usize value_size;
    Compare compare;
};

void tree_construct(struct Tree *tree, usize key_size, usize value_size, Compare compare);
void tree_destruct(struct Tree *tree);
void tree_insert(struct Tree *tree, const void *key, const void *value);
void tree_erase(struct Tree *tree, const void *key);
void tree_contains(const struct Tree *tree, const void *key);
void *tree_at(const struct Tree *tree, const void *key);
