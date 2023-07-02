#pragma once

#include <stdio.h>
#include <time.h>
#include "utility/types.h"

#define BENCH(name, runs) \
static void name##_func_internal(void); \
static void name##_func(void) { \
    clock_t start = clock(); \
    for (usize i = 0; i < runs; i++) \
        name##_func_internal(); \
    clock_t end = clock(); \
    f64 average = ((f64) (end - start)) / runs / CLOCKS_PER_SEC; \
    printf(#name " ran " #runs "x with average time: %fs\n", average); \
} \
static void (*name)(void) = &name##_func; \
static void name##_func_internal(void)
