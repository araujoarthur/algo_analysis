#include <stdlib.h>
#include <stdio.h>
#include "gal.h"

#define PRINT_DEBUG_DATA(T) printf("Length: %d | Capacity: %d | Element Size: %zu\n", T.element_count, T.element_cap, T.element_size)
int main() {
   gal_t test = gal_create(sizeof(char), 0);
   printf("Insertion Tests\n");
   gml_append(&test, 'a');
   PRINT_DEBUG_DATA(test);
   gml_append(&test, 'b');
   PRINT_DEBUG_DATA(test);
   gml_append(&test, 'c');
   PRINT_DEBUG_DATA(test);
   gml_append(&test, 'z');
   PRINT_DEBUG_DATA(test);
   gml_append(&test, 'n');
   PRINT_DEBUG_DATA(test);
   gml_append(&test, 'm');
   PRINT_DEBUG_DATA(test);
   gml_append(&test, 'h');
   PRINT_DEBUG_DATA(test);

   gml_printarr(&test, gml_print_char);

   return 0;
}