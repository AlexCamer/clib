#pragma once

#include "utility/types.h"

typedef usize (*Hash)(const void *);

usize i32_hash(const void *key);
usize i64_hash(const void *key);

usize u32_hash(const void *key);
usize u64_hash(const void *key);
