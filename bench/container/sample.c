#include "test/bench.h"
#include "test/suite.h"

BENCH(stack_push_bench, 10) {
    usize x = 0;
    for (usize i = 0; i < 1 << 24; i++)
        x = i + i;
}

SUITE(stack_push_bench)
