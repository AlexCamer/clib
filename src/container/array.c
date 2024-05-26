#include "container/array.h"
#include "utility/memory.h"
#include <assert.h>
#include <string.h>

void
array_construct(struct Array *array, usize size, usize element_size, bool zero) {
    array->bytes = (zero) ? xcalloc(size, element_size)
                          : xmalloc(size * element_size);
    array->size = size;
    array->element_size = element_size;
    array->zero = zero;
}

void
array_destruct(struct Array *array) {
    xfree(array->bytes);
}

void *
array_get(const struct Array *array, usize index) {
    assert(index < array->size);
    return array->bytes + index * array->element_size;
}

void
array_resize(struct Array *array, usize size) {
    usize new_bytes_size = size * array->element_size;
    array->bytes = xrealloc(array->bytes, new_bytes_size);
    if (array->zero == true && size > array->size) {
        usize old_bytes_size = array->size * array->element_size;
        memset(array->bytes + old_bytes_size, 0, new_bytes_size - old_bytes_size);
    }
    array->size = size;
}
