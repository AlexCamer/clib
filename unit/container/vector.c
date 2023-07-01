#include "container/vector.h"
#include "test/unit.h"

UNIT(vector_construct_unit) {
    struct Vector vector;
    vector.data = NULL;
    vector.size = 1;
    vector.capacity = 0;
    vector.value_size = 0;
    vector_construct(&vector, 5);
    ASSERT(vector.data != NULL);
    ASSERT(vector.size == 0);
    ASSERT(vector.capacity > 0);
    ASSERT(vector.value_size == 5);
    vector_destruct(&vector);
}

UNIT(vector_emplace_unit) {
    struct Vector vector;
    vector_construct(&vector, sizeof(usize));
    for (usize i = 0; i < 256; i++) {
        *vector_emplace_cast(&vector, usize) = i;
        ASSERT(vector.size == i + 1);
        ASSERT(vector.size <= vector.capacity);
        ASSERT(*vector_at_cast(&vector, i, usize) == i);
    }
    vector_destruct(&vector);
}

UNIT(vector_push_unit) {
    struct Vector vector;
    vector_construct(&vector, sizeof(usize));
    for (usize i = 0; i < 256; i++) {
        vector_push(&vector, &i);
        ASSERT(vector.size == i + 1);
        ASSERT(vector.size <= vector.capacity);
        ASSERT(*vector_at_cast(&vector, i, usize) == i);
    }
    vector_destruct(&vector);
}

UNIT(vector_pop_unit) {
    struct Vector vector;
    vector_construct(&vector, sizeof(usize));
    for (usize i = 0; i < 256; i++)
        vector_push(&vector, &i);
    for (usize i = 256; i != 0; i--) {
        vector_pop(&vector);
        ASSERT(vector.size == i - 1);
        ASSERT(*vector_at_cast(&vector, i - 1, usize) == i - 1);
    }
    vector_destruct(&vector);
}

UNIT(vector_at_unit) {
    struct Vector vector;
    vector_construct(&vector, sizeof(usize));
    for (usize i = 0; i < 256; i++)
        vector_push(&vector, &i);
    for (usize i = 0; i < 256; i++)
        ASSERT(*vector_at_cast(&vector, i, usize) == i);
    vector_destruct(&vector);
}

SUITE(vector_construct_unit,
      vector_emplace_unit,
      vector_push_unit,
      vector_pop_unit,
      vector_at_unit)
