#include "container/list.h"
#include "utility/macros.h"
#include <assert.h>

#define LIST_MIN_CAPACITY_LOG_2 4
#define LIST_MIN_CAPACITY EXP_2(LIST_MIN_CAPACITY_LOG_2)

void
list_construct(struct List *list, usize value_size) {
    array_construct(&(list->array), LIST_MIN_CAPACITY, value_size, false);
    list->size = 0;
}

void
list_destruct(struct List *list) {
    array_destruct(&(list->array));
}

void *
list_get(const struct List *list, usize index) {
    assert(index < list->size);
    return array_get(&(list->array), index);
}

void *
list_add(struct List *list) {
    usize capacity = list->array.size;
    if (list->size == capacity) {
        array_resize(&(list->array), MUL_2(capacity));
    }
    return array_get(&(list->array), list->size++);
}

void
list_remove(struct List *list) {
    assert(list->size > 0);
    list->size--;
}

bool
list_empty(const struct List *list) {
    return list->size == 0;
}
