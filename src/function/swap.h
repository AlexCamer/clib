#pragma once

typedef void (*Swap)(void *, void *);

void swap_x8(void *element_1, void *element_2);
void swap_x16(void *element_1, void *element_2);
void swap_x32(void *element_1, void *element_2);
void swap_x64(void *element_1, void *element_2);
void swap_ptr(void *element_1, void *element_2);
