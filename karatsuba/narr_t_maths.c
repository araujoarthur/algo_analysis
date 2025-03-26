#include <stdlib.h>
#include <stdio.h>
#include "narr_t.h"
#include "narr_t_maths.h"

// Performs the subtraction a - b (subtracts b from a)
// This function has the assumption that a-b is still a positive number.
numarray_t* subtract_na(numarray_t* a, numarray_t* b) {
   padeq_na(a, b);

   NUMARRAY_T_DUMP("a", "subtract_na", a);
   NUMARRAY_T_DUMP("b", "subtract_na", b);

   numarray_t* result = clone_na(a);
   int borrow = 0;
   for(int i = 0; i < a->len; i++) {
      // Removes the borrowed digit from the previous position.
      if (borrow > 0) {
         result->num[i] -= borrow;
         borrow = 0;
      }

      // Marks the next field to borrow.
      if (a->num[i] < b->num[i]) {
         result->num[i]+=10;
         borrow++;
      }

      result->num[i] -= b->num[i];
   }

   // Checking if after the loop, borrow is still 1. It means something wen't wrong and b > a
   if (borrow == 1) {
      printf("subtraction failed\na: ");
      printn_na(a);
      printf("b: ");
      printn_na(b);
      exit(EXIT_FAILURE);
   }

   return trim_na(result);
}

// cmon richie, where's my operator overloadinggggg
/*
Assumptions: 
   1. A sum of two positive **single-digit** integers is ALWAYS in the interval [0, 18]
*/
numarray_t* sum_na(numarray_t* a, numarray_t* b) {
   if (a == NULL || b == NULL || a->num == NULL || b->num == NULL) {
      DEBUG_OUTPUT("Returning NULL from sum_na, a, b, a->num or b->num was NULL.\n");
      return NULL;
   }

   int carry = 0;
   numarray_t* result = cremp_na(a->len+b->len);

   if (a->len != b->len) {
      if (a->len > b->len) {
         padr_na(b, a->len - b->len);
      } else {
         padr_na(a, b->len - a->len);
      }
   }

   // doesnt matter if I use a or b's len. Both are the same by definition.
   for(int i = 0; i < a->len; i++) {
      int sum = a->num[i] + b->num[i] + carry;
      carry = 0;

      int adder = sum%10;
      
      if (sum >= 10) {
         carry = 1;
      }

      result->num[i] = adder;
      result->len++;
   }

   if (carry == 1) {
      result->num[result->len++] = carry;
   }

   // Adjustments to the size;
   int* r = realloc(result->num, sizeof(int)*result->len);
   if (r == NULL){
      DEBUG_OUTPUT("Returning NULL from sum_na, r realloc failed.\n");
      return NULL;
   }

   result->num = r;

   return result;
}