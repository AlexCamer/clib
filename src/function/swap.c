#include "function/swap.h"
#include "utility/types.h"

void
swap_x8(void *element_1, void *element_2) {
    u8 *cast_1 = element_1;
    u8 *cast_2 = element_2;
    u8 temp = *cast_1;
    *cast_1 = *cast_2;
    *cast_2 = temp;
}

void
swap_x16(void *element_1, void *element_2) {
    u16 *cast_1 = element_1;
    u16 *cast_2 = element_2;
    u16 temp = *cast_1;
    *cast_1 = *cast_2;
    *cast_2 = temp;
}

void
swap_x32(void *element_1, void *element_2) {
    u32 *cast_1 = element_1;
    u32 *cast_2 = element_2;
    u32 temp = *cast_1;
    *cast_1 = *cast_2;
    *cast_2 = temp;
}

void
swap_x64(void *element_1, void *element_2) {
    u64 *cast_1 = element_1;
    u64 *cast_2 = element_2;
    u64 temp = *cast_1;
    *cast_1 = *cast_2;
    *cast_2 = temp;
}

void
swap_ptr(void *element_1, void *element_2) {
    void **cast_1 = element_1;
    void **cast_2 = element_2;
    void *temp = *cast_1;
    *cast_1 = *cast_2;
    *cast_2 = temp;
}
