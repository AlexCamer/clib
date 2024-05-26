#pragma once

#include "utility/types.h"

void *xmalloc(usize size);
void *xcalloc(usize size, usize element_size);
void *xrealloc(void *ptr, usize size);
void xfree(void *ptr);
