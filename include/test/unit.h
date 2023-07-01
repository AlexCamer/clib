#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "utility/types.h"

#define UNIT(name) \
static void name##_func(void); \
static void (*name)(void) = &name##_func; \
static void name##_func(void)

#define ASSERT(expr) \
do { \
    if (!(expr)) { \
        fprintf(stderr, "Suite failed @ Line: %d\n", __LINE__); \
        exit(1); \
    } \
} while (0)

#define SUITE(...) \
i32 main(void) { \
    void (*suite[])() = { __VA_ARGS__, NULL }; \
    for (usize i = 0; suite[i] != NULL; i++) \
        suite[i](); \
    printf("Suite passed\n"); \
    return 0; \
}
