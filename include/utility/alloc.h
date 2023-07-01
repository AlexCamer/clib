#pragma once

#include "utility/types.h"

void *xmalloc(usize size);
void *xcalloc(usize size, usize value_size);
void *xrealloc(void *ptr, usize size);
void xfree(void *ptr);
