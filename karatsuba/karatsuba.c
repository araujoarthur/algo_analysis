#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "narr_t.h"
#include "narr_t_maths.h"

void printliml_na(int* numArray, int count);



int karatsuba_executions = 0;


/*
This function deserves a little more attention and documentation.

Purpose: To split a numarray_t* into two numarray_t*, and divide equally between two, each ending with n elements.
These return values are stored in an array I called "result".

   Given the expression x = x1 * B^M + x0, x being equivalent to t->num, then:
      THE FIRST element returned by this function is equivalent to x0
      THE SECOND element returned by this function is equivalent to x1

Assumptions:
   1. `n` is correctly defined. This is responsability of the caller.
   2. n is even.

Returns:
   NULL on failure,
   numarray_t** containing two elements on success.

Further Explanation:

One can think as `n` being the amount of bytes copied to each new numarray_t*. It's also true to think
in `n` as the cutting element, i.e. the first index that will be in x1.

It's also worth of note that the code may look weird at first glance *but* consider that the memory layout for
the data structure numarray_t reverses the integer to match the index with it's importance.
This means ultimately that the integer 135792468 would be stored as:
[8, 6, 4, 2, 9, 7, 5, 3, 1].

It's specially useful because we have the following binding:

[8, 6, 4, 2, 9, 7, 5, 3, 1].
 0, 1, 2, 3, 4, 5, 6, 7, 8

And the actual integer stored is 8*10ˆ0 + 6*10ˆ1 + 4*10ˆ2 + 2*10ˆ3 + 9*10ˆ4 + 7*10ˆ5 + 5*10ˆ6 + 3*10ˆ7 + 1*10ˆ8

But can indeed cause some confusion.

From this definition of n (as the first index returned in x1, or the equivalent: half the length of t->num), we derive
That the memory copy must happen in the following way:
    For x0: 
      from t->num to t->num+(n-1), effectively copying n bytes from interval [0, n-1].
   
   For x1:
      from &t->num[n] to t->num+(2n-1), effectively copying n bytes from interval [n, 2n-1].
*/
numarray_t** splem_na(numarray_t* t, int n) {
   if(t == NULL){
      DEBUG_OUTPUT("Returning NULL from splem_na, t was NULL.\n");
      return NULL;
   }
   numarray_t** res = malloc(sizeof(numarray_t*)*2);
   if (res == NULL) {
      DEBUG_OUTPUT("Returning NULL from splem_na, res malloc failed.\n");
      return NULL;
   }

   res[0] = malloc(sizeof(numarray_t));
   if (res[0] == NULL) {
      DEBUG_OUTPUT("To Return NULL from splem_na, res[0] malloc failed.\n");
      free(res);
      DEBUG_OUTPUT("Returning NULL from splem_na, res[0] malloc failed.\n");
      return NULL;
   }

   res[1] = malloc(sizeof(numarray_t));
   if (res[1] == NULL) {
      DEBUG_OUTPUT("To Return (1) NULL from splem_na, res[1] malloc failed.\n");
      free(res[0]);
      DEBUG_OUTPUT("To Return (2) NULL from splem_na, res[1] malloc failed.\n");
      free(res);
      DEBUG_OUTPUT("Returning NULL from splem_na, res[1] malloc failed.\n");
      return NULL;
   }

   res[0]->len = n;
   res[1]->len = n;

   res[0]->num = malloc(sizeof(int) * res[0]->len);
   if (res[0]->num == NULL) {
      DEBUG_OUTPUT("To Return (1) NULL from splem_na, res[0]->num malloc failed.\n");
      free(res[0]);
      DEBUG_OUTPUT("To Return (1) NULL from splem_na, res[0]->num malloc failed.\n");
      free(res[1]);
      DEBUG_OUTPUT("To Return (1) NULL from splem_na, res[0]->num malloc failed.\n");
      free(res);
      return NULL;
   }

   res[1]->num = malloc(sizeof(int)*res[1]->len);
   if (res[1]->num == NULL) {
      DEBUG_OUTPUT("To Return (1) NULL from splem_na, res[1]->num malloc failed.\n");
      free(res[0]->num);
      DEBUG_OUTPUT("To Return (2) NULL from splem_na, res[1]->num malloc failed.\n");
      free(res[0]);
      DEBUG_OUTPUT("To Return (3) NULL from splem_na, res[1]->num malloc failed.\n");
      free(res[1]);
      DEBUG_OUTPUT("To Return (4) NULL from splem_na, res[1]->num malloc failed.\n");
      free(res);
      DEBUG_OUTPUT("Returning NULL from splem_na, res[1]->num malloc failed.\n");
      return NULL;
   }

   memcpy(res[1]->num, &t->num[n], sizeof(int)*n);
   memcpy(res[0]->num, t->num, sizeof(int)*n);

   return res;
}

numarray_t* karatsuba(numarray_t* num_a, numarray_t* num_b){
   DEBUG_OUTPUT_H("\n(%d) - ENTERING KARATSUBA\n", karatsuba_executions++);
   if (num_a == NULL || num_b == NULL || num_a->num == NULL || num_b->num == NULL) {
      DEBUG_OUTPUT("---Returning NULL from karatsuba, num_a, num_b, num_a->num or num_b->num was NULL.\n");
      return NULL;
   }

   NUMARRAY_T_DUMP("num_a", "karatsuba", num_a);

   NUMARRAY_T_DUMP("num_b", "karatsuba", num_b);

   DEBUG_OUTPUT("--Equalizing Padding\n");
   padeq_na(num_a, num_b);

   if (num_a->len == 1 && num_b->len == 1) { // I assume both will be size 1 because I only consider inputs that have power of two length
      int result = num_a->num[0] * num_b->num[0];
      DEBUG_OUTPUT("Just Multiplied!\n");
      DEBUG_OUTPUT_H("num_a->num[0] was %d\n", num_a->num[0]);
      DEBUG_OUTPUT_H("num_b->num[0] was %d\n", num_b->num[0]);
      numarray_t* res_na_t = splint_na(result);
      DEBUG_OUTPUT("--Returning res_na_t\n");
      return res_na_t;
   }

   int new_n;
   new_n = (num_a->len > num_b->len ? num_b->len : num_a->len)/2;
   numarray_t** x = splem_na(num_a, new_n);
   if(x == NULL) {
      DEBUG_OUTPUT("Returning NULL from karatsuba, x was NULL.\n");
      return NULL;
   }

   numarray_t** y = splem_na(num_b, new_n);
   if (y == NULL) {
      DEBUG_OUTPUT("To Return NULL (1) from karatsuba, y was NULL.\n");
      free_na(x[0]);
      DEBUG_OUTPUT("To Return NULL (2) from karatsuba, y was NULL.\n");
      free_na(x[1]);
      DEBUG_OUTPUT("Returning NULL from karatsuba, y was NULL.\n");
      return NULL;
   }

   numarray_t* a = x[0];
   numarray_t* b = x[1];

   numarray_t* c = y[0];
   numarray_t* d = y[1];
   
   DEBUG_OUTPUT("-- Applying SUM at karatsuba\n");
   numarray_t* p = sum_na(a, b);
   DEBUG_OUTPUT("-- Applying SUM at karatsuba\n");
   numarray_t* q = sum_na(c, d);

   DEBUG_OUTPUT("-- Applying MULTIPLICATION ac at karatsuba\n");
   numarray_t* ac = karatsuba(a, c);
   DEBUG_OUTPUT("-- Applying MULTIPLICATION bd at karatsuba\n");
   numarray_t* bd = karatsuba(b, d);

   DEBUG_OUTPUT("-- Applying MULTIPLICATION pq at karatsuba\n");
   numarray_t* pq = karatsuba(p, q);

   DEBUG_OUTPUT("-- Applying SUM of ac+bd z1 at karatsuba\n");
   numarray_t* acbd = sum_na(ac, bd);
   // proceed to subtraction
   
   numarray_t* adbc = subtract_na(pq, acbd); // pq - (ac + bd)


   numarray_t* paddedAC = padl_na(ac, num_a->len);

   numarray_t* paddedADBC = padl_na(adbc, num_a->len/2);
  

   numarray_t* intermediary_sum = sum_na(paddedAC, paddedADBC);
   numarray_t* result = sum_na(intermediary_sum, bd);
   //terminateNumArray(intermediary_sum);
   //terminateNumArray(z0);


   // should I free num_a and num_b and return only the result?
   return trim_na(result);
}

