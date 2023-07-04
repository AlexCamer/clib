#include "container/treemap.h"
#include "test/suite.h"
#include "test/unit.h"

void
random_permutation(u64 *array, usize size) {
    srand(0);
    for (u64 i = 0; i < size; i++)
        array[i] = i;
    for (usize i = size; i > 0; i--) {
        usize swap = rand() % i;
        u64 temp = array[swap];
        array[swap] = array[i - 1];
        array[i - 1] = temp;
    }
}

UNIT(tree_map_construct_unit) {
    struct TreeMap map;
    map.root = (struct TreeMapNode *) 1;
    map.key_size = 0;
    map.value_size = 0;
    map.compare = NULL;
    tree_map_construct(&map, 5, 6, &u64_compare);
    ASSERT(map.root == NULL);
    ASSERT(map.key_size == 5);
    ASSERT(map.value_size == 6);
    ASSERT(map.compare == &u64_compare);
    tree_map_destruct(&map);
}

UNIT(tree_map_emplace_unit) {
    struct TreeMap map;
    tree_map_construct(&map, sizeof(u64), sizeof(u64), &u64_compare);
    u64 array[256];
    random_permutation(array, 256);
    for (u64 i = 0; i < 256; i++)
        *tree_map_emplace_cast(&map, array + i, u64) = i;
    for (u64 i = 0; i < 256; i++)
        ASSERT(*tree_map_at_cast(&map, array + i, u64) == i);
    tree_map_destruct(&map);
}

UNIT(tree_map_insert_unit) {
    struct TreeMap map;
    tree_map_construct(&map, sizeof(u64), sizeof(u64), &u64_compare);
    u64 array[256];
    random_permutation(array, 256);
    for (u64 i = 0; i < 256; i++)
        tree_map_insert(&map, array + i, &i);
    for (u64 i = 0; i < 256; i++)
        ASSERT(*tree_map_at_cast(&map, array + i, u64) == i);
    tree_map_destruct(&map);
}

UNIT(tree_map_erase_unit) {
    struct TreeMap map;
    tree_map_construct(&map, sizeof(u64), sizeof(u64), &u64_compare);
    u64 array[256];
    random_permutation(array, 256);
    for (u64 i = 0; i < 256; i++)
        tree_map_insert(&map, array + i, &i);
    for (u64 i = 0; i < 128; i++)
        tree_map_erase(&map, array + i);
    fprintf(stderr, "Boo\n");
    for (u64 i = 0; i < 128; i++) {
        ASSERT(!tree_map_contains(&map, array + i));
        ASSERT(tree_map_at_cast(&map, array + i + 128, u64) != NULL);
    }
    tree_map_destruct(&map);
}

UNIT(tree_map_iterator) {
    struct TreeMap map;
    tree_map_construct(&map, sizeof(u64), sizeof(u64), &u64_compare);
    u64 array[256];
    random_permutation(array, 256);
    u64 i = 0;
    for (u64 j = array[0] + 1; i < 256; j = array[++i] + 1)
        tree_map_insert(&map, array + i, &j);
    i = 0;
    for (struct TreeMapIterator it = tree_map_iterator_begin(map);
         !tree_map_iterator_end(&it);
         tree_map_iterator_increment(&it))
    {
        ASSERT(*tree_map_iterator_key_cast(it, u64) == array[i]);
        ASSERT(*tree_map_iterator_value_cast(it, u64) == array[i++] + 1);
    }
    i = 255;
    for (struct TreeMapIterator it = tree_map_iterator_rbegin(map);
    !tree_map_iterator_end(&it);
    tree_map_iterator_increment(&it))
    {
        ASSERT(*tree_map_iterator_key_cast(it, u64) == array[i]);
        ASSERT(*tree_map_iterator_value_cast(it, u64) == array[i--] + 1);
    }
    tree_map_destruct(&map);
}

SUITE(tree_map_construct_unit,
      tree_map_emplace_unit,
      tree_map_insert_unit,
      tree_map_erase_unit)
