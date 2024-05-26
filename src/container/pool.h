#pragma once

#include "container/list.h"

struct Pool {
    struct List blocks;
    void *removed;
    usize index;
    usize element_size;
    usize block_size;
};

void pool_construct(struct Pool *pool, usize element_size, usize block_size);
void pool_destruct(struct Pool *pool);
void *pool_add(struct Pool *pool);
void pool_remove(struct Pool *pool, void *element_size);
