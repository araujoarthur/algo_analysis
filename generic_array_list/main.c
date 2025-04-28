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
    gml_append(&test, 'k');
    gml_append(&test, 'a');
    gml_append(&test, 'h');
    gml_append(&test, 'i');
    // Adding sometimes the overlaping sequence klamartkl
    gml_append(&test, 'k');
    gml_append(&test, 'l');
    gml_append(&test, 'a');
    gml_append(&test, 'm');
    gml_append(&test, 'a');
    gml_append(&test, 'r');
    gml_append(&test, 't');
    gml_append(&test, 'k');
    gml_append(&test, 'l');
    //some gibberish
    gml_append(&test, 'k');
    gml_append(&test, 'a');
    gml_append(&test, 'h');
    gml_append(&test, 'i');
    // The sequence again
    gml_append(&test, 'k');
    gml_append(&test, 'l');
    gml_append(&test, 'a');
    gml_append(&test, 'm');
    gml_append(&test, 'a');
    gml_append(&test, 'r');
    gml_append(&test, 't');
    gml_append(&test, 'k');
    gml_append(&test, 'l');
    // Now just the amartkl part
    gml_append(&test, 'a');
    gml_append(&test, 'm');
    gml_append(&test, 'a');
    gml_append(&test, 'r');
    gml_append(&test, 't');
    gml_append(&test, 'k');
    gml_append(&test, 'l');
    

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
    gal_t resultSeq1 = gal_search_all(&test, &searchSeq1);
    printf("1st Expected Length 2, found length %d | Expected Array: [3, 9], Found:\n", resultSeq1.element_count);
    gml_printarr(&resultSeq1, gml_print_int);
    PRINT_DEBUG_DATA(resultSeq1);

    printf("\n\nTesting Second sequence (z,n,m)\n");
    gal_t resultSeq2 = gal_search_all(&test, &searchSeq2);
    printf("2nd Expected Length 1, found length %d | Expected Array [3], found:\n", resultSeq2.element_count);
    gml_printarr(&resultSeq2, gml_print_int);
    PRINT_DEBUG_DATA(resultSeq2);

    printf("\n\nTesting Third sequence (m,h,b,n)\n");
    gal_t resultSeq3 = gal_search_all(&test, &searchSeq3);
    printf("3rd Expected Length 2, found length %d | Expected Array [5, 18], found:\n", resultSeq3.element_count);
    gml_printarr(&resultSeq3, gml_print_int);
    PRINT_DEBUG_DATA(resultSeq3);

    printf("\n\nTesting Foruth sequence (k,k)\n");
    gal_t resultSeq4 = gal_search_all(&test, &searchSeq4);
    printf("4th Expected Length 0, found length %d | Expected Array: [], found:", resultSeq4.element_count);
    gml_printarr(&resultSeq4, gml_print_int);
    PRINT_DEBUG_DATA(resultSeq4);

    printf("\n\nTesting Find z char)\n");
    gal_t resultSeq5 = gml_find_all(&test, 'z');
    printf("5th Expected Length 0, found length %d | Expected Array: [], found:", resultSeq5.element_count);
    gml_printarr(&resultSeq5, gml_print_int);
    PRINT_DEBUG_DATA(resultSeq5);
   return 0;
}
