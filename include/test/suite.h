#pragma once

#include "utility/types.h"

#define SUITE(...) \
i32 main(void) { \
    void (*suite[])() = { __VA_ARGS__, NULL }; \
    for (usize i = 0; suite[i] != NULL; i++) \
        suite[i](); \
    return 0; \
}
