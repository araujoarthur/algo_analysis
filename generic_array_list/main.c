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
    gml_append(&test, 'a'); // IDX 10
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'j'); // IDX 11
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'l'); // IDX 12
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'k'); // IDX 13
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'x'); // IDX 14
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'o'); // IDX 15
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'p'); // IDX 16
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'p'); // IDX 17
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'm'); // IDX 18
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'h'); // IDX 19
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'b'); // IDX 20
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'n'); // IDX 21
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'y'); // IDX 22
    PRINT_DEBUG_DATA(test);
    gml_append(&test, 'd'); // IDX 23
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

    gal_t searchSeq4 = gal_create(sizeof(char), 2);
    gml_append(&searchSeq4, 'k');
    gml_append(&searchSeq4, 'k');
    PRINT_DEBUG_DATA(searchSeq4);

    printf("\n\nTesting First sequence (z)\n");
    int resultSeq1 = gal_search(&test, &searchSeq1);
    printf("1st Expected 3, found %d\n", resultSeq1);

    printf("\n\nTesting Second sequence (z,n,m)\n");
    int resultSeq2 = gal_search(&test, &searchSeq2);
    printf("2nd Expected 3, found %d\n", resultSeq2);

    printf("\n\nTesting Third sequence (m,h,b,n)\n");
    int resultSeq3 = gal_search(&test, &searchSeq3);
    printf("3rd Expected 5, found %d\n", resultSeq3);

    printf("\n\nTesting Foruth sequence (k,k)\n");
    int resultSeq4 = gal_search(&test, &searchSeq4);
    printf("4th Expected -1, found %d\n", resultSeq4);
   return 0;
}
