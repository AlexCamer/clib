#include "container/array.h"
#include "container/pool.h"
#include "utility/macros.h"

void
pool_construct(struct Pool *pool, usize element_size, usize block_size) {
    pool->removed = NULL;
    pool->index = 0;
    pool->element_size = MAX(element_size, sizeof(void *));
    pool->block_size = block_size;
    list_construct(&(pool->blocks), sizeof(struct Array));
}

void
pool_destruct(struct Pool *pool) {
    for (usize i = 0; i < pool->blocks.size; i++) {
        array_destruct(list_get(&(pool->blocks), i));
    }
    list_destruct(&(pool->blocks));
}

void *
pool_add(struct Pool *pool) {
    if (pool->removed != NULL) {
        void **element = pool->removed;
        pool->removed = *element;
        return element;
    }
    if (pool->index == 0) {
        struct Array *block = list_add(&(pool->blocks));
        array_construct(block, pool->block_size, pool->element_size, false);
    }
    struct Array *block = list_get(&(pool->blocks), pool->blocks.size - 1);
    void *element = array_get(block, pool->index);
    pool->index = (pool->index + 1) % pool->block_size;
    return element;
}

void
pool_remove(struct Pool *pool, void *element) {
    void **removed = element;
    *removed = pool->removed;
    pool->removed = removed;
}
