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

   printf("Find Tests:\n");
   char element_to_find = 'b';
   int res = gal_find(&test, &element_to_find);
   printf("Result: %d, expected: 1\n", res);

   element_to_find = 'a';
   res = gal_find(&test, &element_to_find);
   printf("Result: %d, expected: 0\n", res);

   element_to_find = 'h';
   res = gal_find(&test, &element_to_find);
   printf("Result: %d, expected: 6\n", res);

   element_to_find = 'z';
   res = gal_find(&test, &element_to_find);
   printf("Result: %d, expected: 3\n", res);
   
   return 0;
}