#include "container/list.h"
#include "container/pool.h"
#include "utility/suite.h"
#include "utility/test.h"

TEST(pool_test) {
    struct List ptrs;
    struct Pool pool;
    list_construct(&ptrs, sizeof(u64 *));
    pool_construct(&pool, sizeof(u64), 16);
    for (usize i = 0; i < 64; i++) {
        u64 **ptr = list_add(&ptrs);
        *ptr = pool_add(&pool);
        **ptr = 0;
    }
    for (usize i = 0; i < 64; i++) {
        u64 **ptr = list_get(&ptrs, i);
        pool_remove(&pool, *ptr);
    }
    for (usize i = 64; i > 0; i--) {
        u64 **ptr = list_get(&ptrs, i - 1);
        TEST_ASSERT(pool_add(&pool) == *ptr);
    }
    pool_destruct(&pool);
    list_destruct(&ptrs);
}

SUITE(pool_test)
