#include "container/stack.h"
#include "test/unit.h"

UNIT(stack_construct_unit) {
    struct Stack stack;
    stack.top = (struct StackNode *) 1;
    stack.value_size = 0;
    stack_construct(&stack, 5);
    ASSERT(stack.top == NULL);
    ASSERT(stack.value_size == 5);
    stack_destruct(&stack);
}

UNIT(stack_emplace_unit) {
        struct Stack stack;
        stack_construct(&stack, sizeof(usize));
        for (usize i = 0; i < 64; i++) {
            *stack_emplace_cast(&stack, usize) = i;
            ASSERT(*stack_top_cast(&stack, usize) == i);
        }
        stack_destruct(&stack);
}

UNIT(stack_push_unit) {
    struct Stack stack;
    stack_construct(&stack, sizeof(usize));
    for (usize i = 0; i < 64; i++) {
        stack_push(&stack, &i);
        ASSERT(*stack_top_cast(&stack, usize) == i);
    }
    stack_destruct(&stack);
}

UNIT(stack_pop_unit) {
    struct Stack stack;
    stack_construct(&stack, sizeof(usize));
    for (usize i = 0; i < 64; i++)
        stack_push(&stack, (void *) &i);
    for (usize i = 64; i != 0; i--) {
        ASSERT(*((usize *) stack_top(&stack)) == i - 1);
        stack_pop(&stack);
    }
    ASSERT(stack.top == NULL);
    stack_destruct(&stack);
}

SUITE(stack_construct_unit,
      stack_emplace_unit,
      stack_push_unit,
      stack_pop_unit)
