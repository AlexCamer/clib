#include "container/heap.h"
#include "function/compare.h"
#include "function/swap.h"
#include "utility/suite.h"
#include "utility/test.h"

TEST(heap_test) {
    struct Heap heap;
    heap_construct(&heap, 4, sizeof(u64), &compare_u64, &swap_x64);
    TEST_ASSERT(heap_empty(&heap) == true);
    for (usize i = 0; i < 64; i++) {
        u64 element = i;
        heap_add(&heap, &element);
    }
    TEST_ASSERT(heap_empty(&heap) == false);
    for (usize i = 64; i > 0; i--) {
        const u64 *element = heap_get(&heap, 0);
        TEST_ASSERT(*element == i - 1);
        heap_remove(&heap, 0);
    }
    TEST_ASSERT(heap_empty(&heap) == true);
    heap_destruct(&heap);
}

SUITE(heap_test)
