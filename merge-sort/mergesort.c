#include "mergesort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int merge_run = 0;

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
   if (!a || !b) {
      return NULL;
   }

   int i = 0;
   int j = 0;
   int newArrLen = len_a + len_b;
   int* merged = malloc(sizeof(int) * newArrLen);
   if (!merged) {
      return NULL;
   }

   int k = 0;
   for(; i < len_a && j < len_b; k++) {
      merge_run++;
      if (a[i] < b[j]) {
         merged[k] = a[i];
         i++;
      } else {
         merged[k] = b[j];
         j++;
      }
   }

   if (i < len_a) {
      while (i < len_a && k < newArrLen) {
         merged[k] = a[i];
         i++;
         k++;
      }
   } else if (j < len_b) {
      while(j < len_b && k < newArrLen) {
         merged[k] = b[j];
         j++;
         k++;
      }
   }

   if (k < newArrLen) {
      int selector = i < len_a;
      int* notEmpty = selector ? a : b;
      int notFinal = selector ? i : j;

      for(k; k < newArrLen; k++) {
         merged[k] = notEmpty[notFinal++];
      }
   }



   return merged;

}