#include <stdlib.h>
#include <stdio.h>
#include "gal.h"

#define PRINT_DEBUG_DATA(T) printf("Length: %d | Capacity: %d | Element Size: %zu\n", T.element_count, T.element_cap, T.element_size)
int main() {
    gal_t test = gal_create(sizeof(char), 0);
    printf("Insertion Tests\n");
    gml_append(&test, 'a'); // IDX 0
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'b'); // IDX 1
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'c'); // IDX 2
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'z'); // IDX 3
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'n'); // IDX 4
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'm'); // IDX 5
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'h'); // IDX 6
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'b'); // IDX 7 -- 
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'n'); // IDX 8
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'z'); // IDX 9
    PRINT_DEBUG_DATA(test);
    
    gal_t searchSeq1 = gal_create(sizeof(char), 1);
    gml_append(&searchSeq1, 'z');
    PRINT_DEBUG_DATA(searchSeq1);

    gal_t searchSeq2 = gal_create(sizeof(char), 3);
    gml_append(&searchSeq2, 'z');
    gml_append(&searchSeq2, 'n');
    gml_append(&searchSeq2, 'm');
    PRINT_DEBUG_DATA(searchSeq2);

    gal_t searchSeq3 = gal_create(sizeof(char), 4);
    gml_append(&searchSeq3, 'm');
    gml_append(&searchSeq3, 'h');
    gml_append(&searchSeq3, 'b');
    gml_append(&searchSeq3, 'n');
    PRINT_DEBUG_DATA(searchSeq3);

    int resultSeq1 = gal_search(&test, &searchSeq1);
    printf("CONTINUE FROM HERE\n")
   return 0;
}
