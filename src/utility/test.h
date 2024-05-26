#pragma once

#include <stdio.h>
#include <stdlib.h>

#define TEST(name) \
void name##_internal_2(char *test_name); \
void name##_internal_1(void) { \
    name##_internal_2(#name); \
    printf(#name " passed\n"); \
} \
void (*name)(void) = &name##_internal_1; \
void name##_internal_2(char *test_name)

#define TEST_ASSERT(expr) \
do { \
    if (!(expr)) { \
        fprintf(stderr, "%s failed at assertion \"%s\" on line %d\n", test_name, #expr, __LINE__); \
        exit(1); \
    } \
} while (0)
