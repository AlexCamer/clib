#pragma once

#include "container/array.h"
#include "utility/types.h"

struct List {
    struct Array array;
    usize size;
};

void list_construct(struct List *list, usize value_size);
void list_destruct(struct List *list);
void *list_get(const struct List *list, usize index);
void *list_add(struct List *list);
void list_remove(struct List *list);
bool list_empty(const struct List *list);
