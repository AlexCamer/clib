#include "function/compare.h"

i8
compare_i32(const void *element_1, const void *element_2) {
    i32 *cast_1 = (i32 *) element_1;
    i32 *cast_2 = (i32 *) element_2;
    if (*cast_1 > *cast_2) {
        return 1;
    }
    if (*cast_1 < *cast_2) {
        return -1;
    }
    return 0;
}

i8
compare_i64(const void *element_1, const void *element_2) {
    i64 *cast_1 = (i64 *) element_1;
    i64 *cast_2 = (i64 *) element_2;
    if (*cast_1 > *cast_2) {
        return 1;
    }
    if (*cast_1 < *cast_2) {
        return -1;
    }
    return 0;
}

i8
compare_u32(const void *element_1, const void *element_2) {
    u32 *cast_1 = (u32 *) element_1;
    u32 *cast_2 = (u32 *) element_2;
    if (*cast_1 > *cast_2) {
        return 1;
    }
    if (*cast_1 < *cast_2) {
        return -1;
    }
    return 0;
}

i8
compare_u64(const void *element_1, const void *element_2) {
    u64 *cast_1 = (u64 *) element_1;
    u64 *cast_2 = (u64 *) element_2;
    if (*cast_1 > *cast_2) {
        return 1;
    }
    if (*cast_1 < *cast_2) {
        return -1;
    }
    return 0;
}

i8
compare_reverse_i32(const void *element_1, const void *element_2) {
    return compare_i32(element_2, element_1);
}

i8
compare_reverse_i64(const void *element_1, const void *element_2) {
    return compare_i64(element_2, element_1);
}

i8
compare_reverse_u32(const void *element_1, const void *element_2) {
    return compare_u32(element_2, element_1);
}

i8
compare_reverse_u64(const void *element_1, const void *element_2) {
    return compare_u64(element_2, element_1);
}
