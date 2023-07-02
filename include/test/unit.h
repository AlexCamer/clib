#pragma once

#include <stdio.h>
#include <stdlib.h>

#define UNIT(name) \
static void name##_func_internal(char *unit_name); \
static void name##_func(void) { \
    name##_func_internal(#name); \
    printf(#name " \x1B[32mpassed\x1B[0m\n"); \
} \
static void (*name)(void) = &name##_func; \
static void name##_func_internal(char *unit_name)

#define ASSERT(expr) \
do { \
    if (!(expr)) { \
        fprintf(stderr, "%s \x1B[31mfailed\x1B[0m at line: %d\n", unit_name, __LINE__); \
        exit(1); \
    } \
} while (0)
