#include "container/stack.h"
#include "test/bench.h"
#include "test/suite.h"

BENCH(stack_emplace_bench, 10) {
    struct Stack stack;
    stack_construct(&stack, sizeof(usize));
    for (usize i = 0; i < (1 << 24); i++)
        *stack_emplace_cast(&stack, usize) = i;
    stack_destruct(&stack);
}

BENCH(stack_push_bench, 10) {
    struct Stack stack;
    stack_construct(&stack, sizeof(usize));
    for (usize i = 0; i < (1 << 24); i++)
        *stack_emplace_cast(&stack, usize) = i;
    stack_destruct(&stack);
}

SUITE(stack_emplace_bench,
      stack_push_bench)
