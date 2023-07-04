#include <string.h>
#include "container/vector.h"
#include "utility/alloc.h"
#include "utility/macros.h"

#define VECTOR_MIN_CAPACITY 64

void
vector_construct(struct Vector *vector, usize value_size) {
    vector->size = 0;
    vector->capacity = VECTOR_MIN_CAPACITY;
    vector->value_size = value_size;
    vector->data = xcalloc(vector->capacity, vector->value_size);
}

void
vector_destruct(struct Vector *vector) {
    xfree(vector->data);
}

void *vector_emplace(struct Vector *vector) {
    if (vector->size == vector->capacity) {
        vector->capacity = MUL2(vector->capacity);
        vector->data = xrealloc(vector->data, vector->capacity * vector->value_size);
    }
    return vector->data + vector->size++ * vector->value_size;
}

void
vector_push(struct Vector *vector, void *value) {
    memcpy(vector_emplace(vector), value, vector->value_size);
}

void
vector_pop(struct Vector *vector) {
    vector->size--;
}

void *
vector_at(const struct Vector *vector, usize index) {
    return vector->data + index * vector->value_size;
}
