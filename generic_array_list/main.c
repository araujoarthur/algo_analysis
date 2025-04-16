#include <stdlib.h>
#include <stdio.h>
#include "gal.h"

#define PRINT_DEBUG_DATA(T) printf("Length: %d | Capacity: %d | Element Size: %zu\n", T.element_count, T.element_cap, T.element_size)
int main() {
   gal_t test = create_gal(sizeof(char), 0);
   gml_append(&test, 'a');
   PRINT_DEBUG_DATA(test);
   gml_append(&test, 'b');
   PRINT_DEBUG_DATA(test);
   gml_append(&test, 'c');
   PRINT_DEBUG_DATA(test);

   char retract = '0';
   gml_getn(&test, 2, &retract, -1);
   printf("Result: %c\n", retract);

   gml_getn(&test, 1, &retract, -1);
   printf("Result: %c\n", retract);

   gml_getn(&test, 0, &retract, -1);
   printf("Result: %c\n", retract);
   

   return 0;
}