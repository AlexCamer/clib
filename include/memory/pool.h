#pragma once

#include "container/stack.h"
#include "utility/types.h"

struct PoolStack;

struct Pool {
    struct Stack blocks;
    void *freed;
    usize offset;
    usize value_size;
};

void pool_construct(struct Pool *pool, usize value_size, usize block_size);
void pool_destruct(struct Pool *pool);
void *pool_alloc(struct Pool *pool);
void pool_free(struct Pool *pool, void *ptr);
