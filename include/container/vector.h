#pragma once

#include "utility/types.h"

struct Vector {
    byte *data;
    usize size;
    usize capacity;
    usize elementSize;
};

#define Vector_Empty(vector) ((vector)->size == 0)

void Vector_Construct(struct Vector *vector, usize elementSize);
void Vector_Destruct(struct Vector *vector);
void Vector_Push(struct Vector *vector, void *value);
void Vector_Pop(struct Vector *vector);
void *Vector_At(const struct Vector *vector, usize index);
