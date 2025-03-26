#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <math.h>
#include "narr_t.h"



/* CREATION AND FREEING FUNCTIONS */

// Creates an empty numarray_t* with amount-digits space.
numarray_t* cremp_na(int amount){
   numarray_t* result = malloc(sizeof(numarray_t));
   if (result == NULL) {
      DEBUG_OUTPUT("Returning NULL from cremp_na, result malloc failed.\n");
      return NULL;
   }

   result->len = 0; // Yes, zero. The user can set it later
   result->num = malloc(sizeof(int)*amount);
   if (result->num == NULL) {
      DEBUG_OUTPUT("Returning NULL from cremp_na, result->num malloc failed.\n");
      free(result);
      return NULL;
   }

   return result;
}

// creates a new numarray_t from a string
numarray_t* crfch_na(char* inp) {
   if (inp == NULL) {
      DEBUG_OUTPUT("Returning NULL from crfch_na, inp was null.\n");
      return NULL;
   }

   numarray_t* nt = malloc(sizeof(numarray_t));
   if (nt == NULL) {
      DEBUG_OUTPUT("Returning NULL from crfch_na, nt malloc failed.\n");
      return NULL;
   }

   nt->len = strlen(inp);
   nt->num = malloc(sizeof(int) * nt->len);
   if (nt->num == NULL) {
      DEBUG_OUTPUT("To Return NULL from crfch_na, nt->num malloc failed.\n");
      free(nt);
      DEBUG_OUTPUT("Returning NULL from crfch_na, nt->num malloc failed.\n");
      return NULL;
   }

   int i = 0;
   for(char* tracker = inp+nt->len-1; tracker >= inp; tracker--) {
      nt->num[i++] = *tracker - '0';
   }

   return nt;
}

// clones the numarray_t* passed and return a new object without invalidating the old one.
numarray_t* clone_na(numarray_t* a) {
   if (a == NULL || a->num == NULL) {
      DEBUG_OUTPUT("Returning NULL from clone_na, a or a->num was null.\n");
      return NULL;
   }

   numarray_t* clone = malloc(sizeof(numarray_t));
   if (clone == NULL) {
      DEBUG_OUTPUT("Returning NULL from clone_na, clone malloc failed.\n");
      return NULL;
   }

   clone->len = a->len;
   clone->num = malloc(sizeof(int)*clone->len);
   if (clone->num == NULL) {
      DEBUG_OUTPUT("To return NULL from clone_na, clone->num malloc failed.\n");
      free_na(clone);
      DEBUG_OUTPUT("Returning NULL from clone_na, clone->num malloc failed.\n");
      return NULL;
   }

   memcpy(clone->num, a->num, sizeof(int)*clone->len);
   return clone;
}

// Splits an integer into a numarray_t
numarray_t* splint_na(int i) {
   DEBUG_OUTPUT_H("\nENTERING splint_na - (i = %d)\n", i);

   int digitAmount = i > 0 ? ((int) log10((double) i)) + 1 : 1;
   
   numarray_t* nt = malloc(sizeof(numarray_t));
   if (nt == NULL) {
      DEBUG_OUTPUT("Returning NULL from splint_na, nt malloc failed.\n");
      return NULL;
   }

   nt->num = malloc(sizeof(int)*digitAmount);
   if (nt->num == NULL) {
      DEBUG_OUTPUT("To Return NULL from splint_na, nt->num malloc failed.\n");
      free(nt);
      DEBUG_OUTPUT("Returning NULL from splint_na, nt->num malloc failed.\n");
      return NULL;
   }

   nt->len = digitAmount;
   int c = 0;
   while(i>0) {
      nt->num[c++] = i%10;
      i /= 10;
   }

   return nt;
}

// Free a numarray_t
void* free_na(numarray_t* t) {
   void* copyOfAddress = t;

   if (t == NULL) {
      return NULL;
   }

   if (!(t->num == NULL)) {
      free(t->num);
   }

   free(t);

   return copyOfAddress;
}


/* PADDING FUNCTIONS */

/*
The summation will not work if they don't have the same amount of digits. For this reason I wrote this
padr_na function, it takes two parameters:
   - t, a pointer to type numarray_t
   - howMuch, a size_t specifying how many zeros it should pad to the **right** of the memory layout.

The return value is the object pointed by t with the padding corrected.
*/
numarray_t* padr_na(numarray_t* t, size_t howMuch) {
   if (t == NULL || t->num == NULL) {
      DEBUG_OUTPUT("Returning NULL from padr_na, t or t->num was NULL.\n");
      return NULL;
   }

   int* ret = realloc(t->num, sizeof(int)*(t->len + howMuch));
   if (ret == NULL) {
      DEBUG_OUTPUT("Returning NULL from padr_na, realloc failed.\n");
      return NULL;
   }

   t->num = ret;
   memset(&t->num[t->len], 0, howMuch*sizeof(int));

   t->len += howMuch;
   return t;
}

// Guess what it does? Pads to the left of the memory layout
// it's equivalent to multiplying t*10^n
// returns a different numarray_t*
numarray_t* padl_na(numarray_t* t, size_t n) {
   if (t == NULL || t->num == NULL) {
      DEBUG_OUTPUT("Returning NULL from padl_na, t or t->num was NULL.\n");
      return NULL;
   }

   numarray_t* res = malloc(sizeof(int)*(t->len + n));
   if (res == NULL) {
      DEBUG_OUTPUT("Returning NULL from padl_na, malloc failed.\n");
      return NULL;
   }

   if (n == 0) {
      memcpy(res->num, t->num, t->len*sizeof(int));
      res->len=t->len;
      DEBUG_OUTPUT("Returning early from padl_na, n was 0.\n");
      return res;
   }

   res->num = calloc((t->len + n), sizeof(int));
   if (res->num == NULL) {
      free_na(res);
      DEBUG_OUTPUT("Returning NULL from padl_na, calloc failed.\n");
      return NULL;
   }

   memcpy(&res->num[n], t->num, sizeof(int)*t->len);
   res->len = n + t->len;
   return res;
}

// Takes a pointer to numarray_t, removes all leading zeros (to the right in memory layout)
// Returns t without trailling zeros and with the correct length.
numarray_t* trim_na(numarray_t* t) {
   if (t == NULL || t->num == NULL) {
      DEBUG_OUTPUT("Returning NULL from trim_na, t was NULL.\n");
      return NULL;
   }

   int zeroCount = 0;
   int lastidx = t->len-1;

   for(int i = t->len-1; i >= 0; i--) {
      if (t->num[i] != 0) {
         break;
      }
      zeroCount++;
      lastidx = i;
   }

   int newlen = t->len - zeroCount;
   int* old_num = t->num;
   
   int* new_num = realloc(t->num, sizeof(int)*newlen);
   if (new_num == NULL) {
      DEBUG_OUTPUT("Returning NULL from trim_na, realloc failed.\n");
      return NULL;
   }

   t->num = new_num;
   t->len = newlen;

   return t;
}

// Equalizes the digit length between a and b by adding 0's to the beginning of the one with the smaller length.
void padeq_na(numarray_t* a, numarray_t* b) {
   if (a == NULL || b == NULL || a->num == NULL || b->num == NULL) {
      DEBUG_OUTPUT("Returning early from padeq_na, a, b, a->num or b->num was NULL.\n");
      return;
   }

   if(a->len == b->len) {
      DEBUG_OUTPUT("Returning early from padeq_na, both had same length.\n");
      return;
   }

   if(a->len > b->len) {
      padr_na(b, a->len - b->len);
      return;
   }

   padr_na(a, b->len - a->len);
   return;
}

/* PRINTING FUNCTIONS */

// Displays in the numarray_t number in the expected orientation.
void printn_na(numarray_t* t) {
   if (t == NULL || t->num == NULL) {
      return;
   }
   
   for(int i = t->len-1; i >= 0; i--) {
      printf("%d", t->num[i]);
   }

   printf("\n");
}

// prints the numarray up to an amout of characters.
void printliml_na(int* numArray, int count) {
   for(int n = 0; n < count; n++) {
      printf("%d",numArray[n]);
   }

   printf("\n");
}