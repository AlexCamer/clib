#pragma once

#include "utility/types.h"

typedef i8 (*Compare)(const void *, const void *);

i8 compare_i32(const void *value_1, const void *value_2);
i8 compare_i64(const void *value_1, const void *value_2);
i8 compare_u32(const void *value_1, const void *value_2);
i8 compare_u64(const void *value_1, const void *value_2);

i8 compare_reverse_i32(const void *value_1, const void *value_2);
i8 compare_reverse_i64(const void *value_1, const void *value_2);
i8 compare_reverse_u32(const void *value_1, const void *value_2);
i8 compare_reverse_u64(const void *value_1, const void *value_2);
