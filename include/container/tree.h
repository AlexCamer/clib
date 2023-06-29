#pragma once

#include "utility/functions.h"
#include "utility/types.h"

struct TreeNode;

struct Tree {
    struct TreeNode *root;
    usize keySize;
    usize valueSize;
    Compare compare;
};

void Tree_Construct(struct Tree *tree, usize keySize, usize valueSize, Compare compare);
void Tree_Destruct(struct Tree *tree);
void Tree_Insert(struct Tree *tree, const void *key, const void *value);
void Tree_Erase(struct Tree *tree, const void *key);
void Tree_Contains(const struct Tree *tree, const void *key);
void *Tree_At(const struct Tree *tree, const void *key);
