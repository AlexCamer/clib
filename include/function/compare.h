#pragma once

#include "utility/types.h"

typedef i8 (*Compare)(const void *, const void *);

i8 i8_compare(const void *value1, const void *value2);
i8 i8_compare_reverse(const void *value1, const void *value2);

i8 i16_compare(const void *value1, const void *value2);
i8 i16_compare_reverse(const void *value1, const void *value2);

i8 i32_compare(const void *value1, const void *value2);
i8 i32_compare_reverse(const void *value1, const void *value2);

i8 i64_compare(const void *value1, const void *value2);
i8 i64_compare_reverse(const void *value1, const void *value2);

i8 u8_compare(const void *value1, const void *value2);
i8 u8_compare_reverse(const void *value1, const void *value2);

i8 u16_compare(const void *value1, const void *value2);
i8 u16_compare_reverse(const void *value1, const void *value2);

i8 u32_compare(const void *value1, const void *value2);
i8 u32_compare_reverse(const void *value1, const void *value2);

i8 u64_compare(const void *value1, const void *value2);
i8 u64_compare_reverse(const void *value1, const void *value2);
