#pragma once

#include "utility/types.h"

struct Vector {
    byte *data;
    usize size;
    usize capacity;
    usize value_size;
};

#define vector_empty(vector) ((vector)->size == 0)
#define vector_emplace_cast(vector, type) ((type *) vector_emplace(vector))
#define vector_at_cast(vector, index, type) ((type *) vector_at(vector, index))

void vector_construct(struct Vector *vector, usize value_size);
void vector_destruct(struct Vector *vector);
void *vector_emplace(struct Vector *vector);
void vector_push(struct Vector *vector, void *value);
void vector_pop(struct Vector *vector);
void *vector_at(const struct Vector *vector, usize index);
