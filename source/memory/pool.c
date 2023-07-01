#include "memory/pool.h"
#include "utility/alloc.h"
#include "utility/macros.h"

void pool_construct(struct Pool *pool, usize value_size, usize block_size) {
    pool->freed = NULL;
    pool->offset = 0;
    pool->value_size = value_size;
    stack_construct(&(pool->blocks), block_size * MAX(PAD_EXP2(value_size, 2), sizeof(void *)));
    stack_emplace(&(pool->blocks));
}

void pool_destruct(struct Pool *pool) {
    stack_destruct(&(pool->blocks));
}

void *pool_alloc(struct Pool *pool) {
    if (pool->freed != NULL) {
        void **ptr = pool->freed;
        pool->freed = *ptr;
        return ptr;
    }
    if (pool->offset == pool->blocks.value_size) {
        pool->offset = 0;
        stack_emplace(&(pool->blocks));
    }
    void *ptr = stack_top_cast(&(pool->blocks), byte) + pool->offset;
    pool->offset += MAX(PAD_EXP2(pool->value_size, 2), sizeof(void *));
    return ptr;
}

void pool_free(struct Pool *pool, void *ptr) {
    void **freed = ptr;
    *freed = pool->freed;
    pool->freed = freed;
}
