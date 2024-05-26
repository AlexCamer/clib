#pragma once

#include "utility/types.h"
#include <stdio.h>
#include <time.h>

#define BENCH(name, runs) \
void name##_internal_2(clock_t *suspend); \
void name##_internal_1(void) { \
    clock_t dummy = 0; \
    usize warmups = runs / 2; \
    for (usize i = 0; i < warmups; i++) { \
        name##_internal_2(&dummy); \
    } \
    clock_t suspend = 0; \
    clock_t start = clock(); \
    for (usize i = 0; i < runs; i++) { \
        name##_internal_2(&suspend); \
    } \
    clock_t end = clock(); \
    f32 average = ((f32) (end - start - suspend)) / runs / CLOCKS_PER_SEC; \
    printf(#name " ran %dx with average time: %fs\n", runs, average); \
} \
void (*name)(void) = &name##_internal_1; \
void name##_internal_2(clock_t *suspend)

#define BENCH_SUSPEND \
for (clock_t start = clock(), done = 0; done == 0; *suspend += clock() - start, done = 1)
