#pragma once

#include "utility/types.h"

typedef u64 (*Hash)(const void *);

u64 hash_x32(const void *key);
u64 hash_x64(const void *key);
