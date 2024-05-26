#pragma once

#include "container/list.h"
#include "function/compare.h"
#include "function/swap.h"

struct Heap {
    struct List list;
    usize children;
    Compare compare;
    Swap swap;
};

void heap_construct(struct Heap *heap, usize children, usize element_size, Compare compare, Swap swap);
void heap_destruct(struct Heap *heap);
const void *heap_get(const struct Heap *heap, usize index);
void heap_add(struct Heap *heap, const void *element);
void heap_remove(struct Heap *heap, usize index);
bool heap_empty(const struct Heap *heap);
usize heap_parent(const struct Heap *heap, usize index);
void heap_children(const struct Heap *heap, usize index, usize *range);
