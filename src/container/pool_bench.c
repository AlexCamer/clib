#include "container/list.h"
#include "container/pool.h"
#include "utility/bench.h"
#include "utility/memory.h"
#include "utility/suite.h"
#include "utility/swap.h"
#include <stdlib.h>

#define POOL_BENCH_RUNS 10
#define POOL_BENCH_SIZE (1 << 24)

BENCH(pool_bench, POOL_BENCH_RUNS) {
    struct List ptrs;
    struct Pool pool;
    list_construct(&ptrs, sizeof(u64 *));
    pool_construct(&pool, sizeof(u64), 1 << 10);
    for (usize i = 0; i < POOL_BENCH_SIZE; i++) {
        u64 **ptr = list_add(&ptrs);
        *ptr = pool_add(&pool);
        **ptr = 0;
    }
    for (usize i = POOL_BENCH_SIZE; i > 0; i--) {
        usize i = rand() % i;
        u64 **ptr = list_get(&ptrs, i);
        pool_remove(&pool, *ptr);
        swap_ptr(ptr, list_get(&ptrs, i - 1));
        list_remove(&ptrs);
    }
    pool_destruct(&pool);
    list_destruct(&ptrs);
}

BENCH(no_pool_bench, POOL_BENCH_RUNS) {
    struct List ptrs;
    list_construct(&ptrs, sizeof(u64 *));
    for (usize i = 0; i < POOL_BENCH_SIZE; i++) {
        u64 **ptr = list_add(&ptrs);
        *ptr = xmalloc(sizeof(u64 *));
        **ptr = 0;
    }
    for (usize i = POOL_BENCH_SIZE; i > 0; i--) {
        usize i = rand() % i;
        u64 **ptr = list_get(&ptrs, i);
        xfree(*ptr);
        swap_ptr(ptr, list_get(&ptrs, i - 1));
        list_remove(&ptrs);
    }
    list_destruct(&ptrs);
}

SUITE(pool_bench,
      no_pool_bench)
