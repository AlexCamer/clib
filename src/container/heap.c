#include "container/heap.h"
#include "utility/macros.h"
#include <assert.h>
#include <string.h>

static inline i8
heap_compare(const struct Heap *heap, usize index_1, usize index_2) {
    const struct List *list = &(heap->list);
    const void *value_1 = list_get(list, index_1);
    const void *value_2 = list_get(list, index_2);
    return heap->compare(value_1, value_2);
}

static inline void
heap_swap(struct Heap *heap, usize index_1, usize index_2) {
    struct List *list = &(heap->list);
    void *value_1 = list_get(list, index_1);
    void *value_2 = list_get(list, index_2);
    heap->swap(value_1, value_2);
}

static inline bool
heap_fix_up(struct Heap *heap, usize index) {
    bool updated = false;
    for (usize parent; index > 0; index = parent) {
        parent = heap_parent(heap, index);
        if (heap_compare(heap, parent, index) > 0) {
            break;
        }
        heap_swap(heap, parent, index);
        updated = true;
    }
    return updated;
}

static inline bool
heap_fix_down(struct Heap *heap, usize index) {
    bool updated = false;
    for (usize parent = index;; index = parent) {
        usize range[2];
        heap_children(heap, index, range);
        for (usize child = range[0]; child < range[1]; child++) {
            if (heap_compare(heap, parent, child) < 0) {
                parent = child;
            }
        }
        if (parent == index) {
            break;
        }
        heap_swap(heap, parent, index);
        updated = true;
    }
    return updated;
}

void
heap_construct(struct Heap *heap, usize children, usize value_size, Compare compare, Swap swap) {
    list_construct(&(heap->list), value_size);
    heap->children = children;
    heap->compare = compare;
    heap->swap = swap;
}

void
heap_destruct(struct Heap *heap) {
    list_destruct(&(heap->list));
}

const void *
heap_get(const struct Heap *heap, usize index) {
    assert(heap->list.size > index);
    return list_get(&(heap->list), index);
}

void
heap_add(struct Heap *heap, const void *element) {
    memcpy(list_add(&(heap->list)), element, heap->list.array.element_size);
    heap_fix_up(heap, heap->list.size - 1);
}

void
heap_remove(struct Heap *heap, usize index) {
    usize size = heap->list.size;
    assert(size > index);
    heap_swap(heap, 0, size - 1);
    list_remove(&(heap->list));
    heap_empty(heap) == true || heap_fix_up(heap, index) == true || heap_fix_down(heap, index);
}

bool
heap_empty(const struct Heap *heap) {
    return list_empty(&(heap->list));
}

usize
heap_parent(const struct Heap *heap, usize index) {
    return (index - 1) / heap->children;
}

void
heap_children(const struct Heap *heap, usize index, usize *range) {
    range[0] = index * heap->children + 1;
    range[1] = MIN(range[0] + heap->children, heap->list.size);
}
