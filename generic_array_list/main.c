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

   printf("\nInsertion Tests\n");
   PRINT_DEBUG_DATA(test);
   gml_printarr(&test, gml_print_char);
   char jk = 'J';
   printf("Inserting 'J' to index 3\n");
   gml_insert_at(&test, 3, 'B');
   char at_idx_3 = 'A';
   PRINT_DEBUG_DATA(test);
   gml_getn(&test, 3, &at_idx_3, 'A');
   printf("Element at index 3: %c\n", at_idx_3);
   gml_printarr(&test, gml_print_char);
   printf("-----------\n");

   printf("\n\nPop Tests\n\n");
   PRINT_DEBUG_DATA(test);
   gml_printarr(&test, gml_print_char);
   printf("\n");
   gal_pop(&test, NULL);
   PRINT_DEBUG_DATA(test);
   gml_printarr(&test, gml_print_char);
   
   gml_pop(&test, NULL, 'A');
   PRINT_DEBUG_DATA(test);
   gml_printarr(&test, gml_print_char);

   gml_append(&test, 'p'); // IDX 5
   PRINT_DEBUG_DATA(test);
   gml_printarr(&test, gml_print_char);

   return 0;
}