#include "container/list.h"
#include "utility/suite.h"
#include "utility/test.h"

TEST(list_test) {
    struct List list;
    list_construct(&list, sizeof(u64));
    TEST_ASSERT(list_empty(&list) == true);
    for (usize i = 0; i < 64; i++) {
        u64 *element = list_add(&list);
        *element = i;
    }
    TEST_ASSERT(list_empty(&list) == false);
    for (usize i = list.size; i > 0; i--) {
        u64 *element = list_get(&list, i - 1);
        TEST_ASSERT(*element == i - 1);
        list_remove(&list);
    }
    TEST_ASSERT(list_empty(&list) == true);
    list_destruct(&list);
}

SUITE(list_test)
