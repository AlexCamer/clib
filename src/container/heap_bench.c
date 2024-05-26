#include "container/heap.h"
#include "utility/bench.h"
#include "utility/compare.h"
#include "utility/suite.h"
#include "utility/swap.h"
#include <stdlib.h>

#define HEAP_BENCH_SIZE (1 << 20)

BENCH(heap_bench, 10) {
    struct Heap heap;
    heap_construct(&heap, 4, sizeof(u64), &compare_u64, &swap_x32);
    for (usize i = 0; i < HEAP_BENCH_SIZE; i++) {
        u64 value = rand();
        heap_add(&heap, &value);
    }
    for (usize i = 0; i < HEAP_BENCH_SIZE; i++) {
        heap_remove(&heap, 0);
    }
    heap_destruct(&heap);
}

SUITE(heap_bench)
