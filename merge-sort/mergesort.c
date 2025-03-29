#include "mergesort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int** split_array(int* arr, size_t len) {
   size_t hct = HCT(len);
   size_t lct = LCT(len);

   int** result = malloc(sizeof(int*) * 2);
   if (!result) {
      return NULL;
   }

   int* left_half = malloc(sizeof(int)*lct);
   if (!left_half) {
      free(result);
      return NULL;
   }

   int* right_half = malloc(sizeof(int)*hct);
   if (!right_half) {
      free(left_half);
      free(result);
      return NULL;
   }

   memcpy(left_half, arr, sizeof(int) * lct);
   memcpy(right_half, arr+lct, sizeof(int) * hct);

   result[0] = left_half;
   result[1] = right_half;

   return result;
}

int* merge_sort(int* arr, size_t len) {
   if (len <= 1) { // base case
      return arr; // already sorted.
   }

   int** splitting = split_array(arr, len);
   if (!splitting) {
      printf("Something went really wrong\n");
      exit(EXIT_FAILURE);
   }

   int* fh = splitting[0];
   size_t fh_len = LCT(len);

   int* sh = splitting[1];
   size_t sh_len = HCT(len);

   int* ms_fh = merge_sort(fh, fh_len);
   int* ms_sh = merge_sort(sh, sh_len);

   int* merged = merge(ms_fh, ms_sh, fh_len, sh_len);
   return merged;
}

int* merge(int* a, int* b, size_t len_a, size_t len_b) {
   return NULL;
}