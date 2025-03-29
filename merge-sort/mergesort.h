#pragma once
#include <stddef.h>

#define HCT(T) T - T/2
#define LCT(T) T/2
int* merge_sort(int* arr, size_t len);
int* merge(int* a, int* b, size_t len_a, size_t len_b);
int** split_array(int* arr, size_t len);