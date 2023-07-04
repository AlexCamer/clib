#pragma once

#include "container/vector.h"
#include "function/compare.h"

struct Heap {
    struct Vector vector;
    Compare compare;
};

#define heap_destruct(heap) vector_destruct(&((heap)->vector))
#define heap_top(heap, index) vector_at(&((heap)->vector), index)
#define heap_top_cast(heap, index, type) vector_at_cast(&((heap)->vector), index, type)

void heap_construct(struct Heap *heap, usize value_size, Compare compare);
void heap_push(struct Heap *heap, const void *value);
void heap_pop(struct Heap *heap);
