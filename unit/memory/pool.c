#include "memory/pool.h"
#include "test/suite.h"
#include "test/unit.h"

#define POOL_VALUE_SIZE 29
#define POOL_BLOCK_SIZE 73
#define POOL_BLOCK_COUNT 5

UNIT(pool_construct_unit) {
    struct Pool pool;
    pool.freed = (void *) 1;
    pool.offset = 1;
    pool.value_size = 0;
    pool_construct(&pool, POOL_VALUE_SIZE, POOL_BLOCK_SIZE);
    ASSERT(pool.freed == NULL);
    ASSERT(pool.offset == 0);
    ASSERT(pool.value_size == POOL_VALUE_SIZE);
    pool_destruct(&pool);
}

UNIT(pool_alloc_unit) {
    struct Pool pool;
    pool_construct(&pool, POOL_VALUE_SIZE, POOL_BLOCK_SIZE);
    for (usize i = 0; i < POOL_BLOCK_COUNT; i++) {
        pool_alloc(&pool);
        for (usize j = 1; j < POOL_BLOCK_SIZE; j++)
            ASSERT(stack_top_cast(&(pool.blocks), byte) + pool.offset == pool_alloc(&pool));
    }
    pool_destruct(&pool);
}

UNIT(pool_free_unit) {
    struct Pool pool;
    pool_construct(&pool, POOL_VALUE_SIZE, POOL_BLOCK_SIZE);
    void *ptrs[POOL_VALUE_SIZE][POOL_BLOCK_SIZE];
    for (usize i = 0; i < POOL_BLOCK_COUNT; i++) {
        for (int j = 0; j < POOL_BLOCK_SIZE; j++)
            ptrs[i][j] = pool_alloc(&pool);
    }
    for (usize i = 0; i < POOL_BLOCK_SIZE; i++) {
        for (int j = 0; j < POOL_BLOCK_COUNT; j++)
            pool_free(&pool, ptrs[j][i]);
    }
    for (isize i = POOL_BLOCK_SIZE - 1; i >= 0; i--) {
        for (int j = POOL_BLOCK_COUNT - 1; j >= 0; j--)
            ASSERT(pool_alloc(&pool) == ptrs[j][i]);
    }
    ASSERT(pool.freed == NULL);
    pool_destruct(&pool);
}

SUITE(pool_construct_unit,
      pool_alloc_unit,
      pool_free_unit)
