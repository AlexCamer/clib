#pragma once

#include "utility/types.h"

struct ListNode;

struct List {
    struct ListNode *front;
    struct ListNode *back;
    usize value_size;
};

#define list_empty(list) ((list)->front == NULL)
#define list_emplace_front_cast(list, type) ((type *) list_emplace_front(list))
#define list_emplace_back_cast(list, type) ((type *) list_emplace_back(list))
#define list_front_cast(list, type) ((type *) (list->front))
#define list_back_cast(list, type) ((type *) (list->back))

void list_construct(struct List *list, usize value_size);
void list_destruct(struct List *list);
void list_emplace_front(struct List *list);
void list_emplace_back(struct List *list);
void list_push_front(struct List *list, const void *value);
void list_push_back(struct List *list, const void *value);
void list_pop_front(struct List *list);
void list_pop_back(struct List *list);

struct ListIterator {
    struct List *list;
    struct ListNode *node;
};

#define list_iterator_end(it) ((it)->node == NULL)
#define list_iterator_value_cast(it, type) ((type *) (list_iterator_value(it)))

struct ListIterator list_iterator_begin(struct List *list);
void list_iterator_next(struct ListIterator *it);
void *list_iterator_value(struct ListIterator *it);
void list_iterator_erase(struct ListIterator *it);
