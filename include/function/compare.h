#pragma once

#include "utility/types.h"

typedef i32 (*Compare)(const void *, const void *);

i32 i8_compare(const void *element1, const void *element2);
i32 i16_compare(const void *element1, const void *element2);
i32 i32_compare(const void *element1, const void *element2);
i32 i64_compare(const void *element1, const void *element2);

i32 u8_compare(const void *element1, const void *element2);
i32 u16_compare(const void *element1, const void *element2);
i32 u32_compare(const void *element1, const void *element2);
i32 u64_compare(const void *element1, const void *element2);
