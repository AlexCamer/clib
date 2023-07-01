#include <stdio.h>
#include <stdlib.h>
#include "utility/alloc.h"

static inline void
xoom(void) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

void *
xmalloc(usize size) {
    void *ptr = malloc(size);
    if (ptr == NULL)
        xoom();
    return ptr;
}

void *
xcalloc(usize size, usize value_size) {
    void *ptr = calloc(size, value_size);
    if (ptr == NULL)
        xoom();
    return ptr;
}

void *
xrealloc(void *ptr, usize size) {
    ptr = realloc(ptr, size);
    if (ptr == NULL)
        xoom();
    return ptr;
}

void
xfree(void *ptr) {
    free(ptr);
}
