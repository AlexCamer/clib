#include "function/compare.h"

i8
i8_compare(const void *value1, const void *value2) {
    i8 *cast1 = (i8 *) value1;
    i8 *cast2 = (i8 *) value2;
    if (*cast1 > *cast2)
        return 1;
    if (*cast1 < *cast2)
        return -1;
    return 0;
}

i8
i8_compare_reverse(const void *value1, const void *value2) {
    return i8_compare(value2, value1);
}

i8
i16_compare(const void *value1, const void *value2) {
    i16 *cast1 = (i16 *) value1;
    i16 *cast2 = (i16 *) value2;
    if (*cast1 > *cast2)
        return 1;
    if (*cast1 < *cast2)
        return -1;
    return 0;
}

i8
i16_compare_reverse(const void *value1, const void *value2) {
    return i16_compare(value2, value1);
}

i8
i32_compare(const void *value1, const void *value2) {
    i32 *cast1 = (i32 *) value1;
    i32 *cast2 = (i32 *) value2;
    if (*cast1 > *cast2)
        return 1;
    if (*cast1 < *cast2)
        return -1;
    return 0;
}

i8
i32_compare_reverse(const void *value1, const void *value2) {
    return i32_compare(value2, value1);
}

i8
i64_compare(const void *value1, const void *value2) {
    i64 *cast1 = (i64 *) value1;
    i64 *cast2 = (i64 *) value2;
    if (*cast1 > *cast2)
        return 1;
    if (*cast1 < *cast2)
        return -1;
    return 0;
}

i8
i64_compare_reverse(const void *value1, const void *value2) {
    return i64_compare(value2, value1);
}

i8
u8_compare(const void *value1, const void *value2) {
    u8 *cast1 = (u8 *) value1;
    u8 *cast2 = (u8 *) value2;
    if (*cast1 > *cast2)
        return 1;
    if (*cast1 < *cast2)
        return -1;
    return 0;
}

i8
u8_compare_reverse(const void *value1, const void *value2) {
    return u8_compare(value2, value1);
}

i8
u16_compare(const void *value1, const void *value2) {
    u16 *cast1 = (u16 *) value1;
    u16 *cast2 = (u16 *) value2;
    if (*cast1 > *cast2)
        return 1;
    if (*cast1 < *cast2)
        return -1;
    return 0;
}

i8
u16_compare_reverse(const void *value1, const void *value2) {
    return u16_compare(value2, value1);
}

i8
u32_compare(const void *value1, const void *value2) {
    u32 *cast1 = (u32 *) value1;
    u32 *cast2 = (u32 *) value2;
    if (*cast1 > *cast2)
        return 1;
    if (*cast1 < *cast2)
        return -1;
    return 0;
}

i8
u32_compare_reverse(const void *value1, const void *value2) {
    return u32_compare(value2, value1);
}

i8
u64_compare(const void *value1, const void *value2) {
    u64 *cast1 = (u64 *) value1;
    u64 *cast2 = (u64 *) value2;
    if (*cast1 > *cast2)
        return 1;
    if (*cast1 < *cast2)
        return -1;
    return 0;
}

i8
u64_compare_reverse(const void *value1, const void *value2) {
    return u64_compare(value2, value1);
}
