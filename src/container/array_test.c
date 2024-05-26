#include "container/array.h"
#include "utility/suite.h"
#include "utility/test.h"

TEST(array_test) {
    struct Array array;
    array_construct(&array, 32, sizeof(u64), false);
    for (usize i = 0; i < 32; i++) {
        u64 *element = array_get(&array, i);
        *element = i;
    }
    array_resize(&array, 64);
    for (usize i = 32; i < 64; i++) {
        u64 *element = array_get(&array, i);
        *element = i;
    }
    for (usize i = 0; i < 64; i++) {
        u64 *element = array_get(&array, i);
        TEST_ASSERT(*element == i);
    }
    array_destruct(&array);
}

TEST(array_zero_test) {
    struct Array array;
    array_construct(&array, 32, sizeof(u64), true);
    for (usize i = 0; i < 32; i++) {
        u64 *element = array_get(&array, i);
        TEST_ASSERT(*element == 0);
        *element = i;
    }
    array_resize(&array, 64);
    for (usize i = 32; i < 64; i++) {
        u64 *element = array_get(&array, i);
        TEST_ASSERT(*element == 0);
        *element = i;
    }
    for (usize i = 0; i < 64; i++) {
        u64 *element = array_get(&array, i);
        TEST_ASSERT(*element == i);
    }
    array_destruct(&array);
}

SUITE(array_test,
      array_zero_test)
