#pragma once

#include "utility/memory.h"
#include "utility/types.h"

struct Array {
    byte *bytes;
    usize size;
    usize element_size;
    bool zero;
};

void array_construct(struct Array *array, usize size, usize value_size, bool zero);
void array_destruct(struct Array *array);
void *array_get(const struct Array *array, usize index);
void array_resize(struct Array *array, usize size);
