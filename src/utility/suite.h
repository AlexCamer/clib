#pragma once

#include "utility/types.h"

#define SUITE(...) \
i32 main(void) { \
    void (*suite[])(void) = { __VA_ARGS__, NULL }; \
    for (usize i = 0; suite[i] != NULL; i++) { \
        suite[i]();\
    } \
    return 0; \
}

#define SETUP \
void setup(void)

#define TEARDOWN \
void teardown(void)

//void setup(void) __attribute__((weak));
//void teardown(void) __attribute__((weak));
