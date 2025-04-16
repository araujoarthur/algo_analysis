#pragma once

#include <stdlib.h>

typedef char* RAW_MEMORY_OFFSET;

typedef struct GenericArrayList {
    void* elements;
    size_t element_size;
    int element_count;
} gal_t, *pgal_t;


gal_t create_gal(size_t element_size, int element_count);
gal_t create_gal_chr(int element_count);



