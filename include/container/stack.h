#pragma once

#include "utility/types.h"

struct StackNode;

struct Stack {
    struct StackNode *top;
    usize value_size;
};

#define stack_empty(stack) ((stack)->top == NULL)
#define stack_emplace_cast(stack, type) ((type *) stack_emplace(stack))
#define stack_top_cast(stack, type) ((type *) stack_top(stack))

void stack_construct(struct Stack *stack, usize value_size);
void stack_destruct(struct Stack *stack);
void *stack_emplace(struct Stack *stack);
void stack_push(struct Stack *stack, void *value);
void stack_pop(struct Stack *stack);
void *stack_top(const struct Stack *stack);
