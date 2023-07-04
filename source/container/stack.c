#include <string.h>
#include "container/stack.h"
#include "utility/alloc.h"

struct StackNode {
    struct StackNode *next;
};

void
stack_construct(struct Stack *stack, usize value_size) {
    stack->top = NULL;
    stack->value_size = value_size;
}

void
stack_destruct(struct Stack *stack) {
    while (!stack_empty(stack))
        stack_pop(stack);
}

void *
stack_emplace(struct Stack *stack) {
    struct StackNode *top = stack->top;
    stack->top = xmalloc(sizeof(struct StackNode) + stack->value_size);
    stack->top->next = top;
    return stack_top(stack);
}

void
stack_push(struct Stack *stack, void *value) {
    memcpy(stack_emplace(stack), value, stack->value_size);
}

void
stack_pop(struct Stack *stack) {
    struct StackNode *node = stack->top;
    stack->top = node->next;
    xfree(node);
}

void *
stack_top(const struct Stack *stack) {
    return stack->top + 1;
}
