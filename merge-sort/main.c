#include <stdlib.h>
#include <stdio.h>
#include "mergesort.h"

#define LEN(T,I) sizeof(T)/sizeof(I)

void printarray(int* a, size_t len) {
   printf("[");
   for (size_t i = 0; i < len; i++) {
      printf("%d%s", a[i], i < len - 1 ? ", ":"]");
   }
   printf("\n");
}

int main() {
   int array[11] = {0, 3, 4, 5, 6, 7, 9, 11, 12, 1, 13};
   printf("%zu %d\n", LEN(array,int), array[1]);
   int** splitter = split_array(array, LEN(array, int));
   int* first_half = splitter[0];
   int* second_half = splitter[1];
   size_t first_half_len = LCT(LEN(array, int));
   size_t second_half_len = HCT(LEN(array, int));

   printarray(array, LEN(array, int));
   printarray(first_half, first_half_len);
   printarray(second_half, second_half_len);
   return 1;
}