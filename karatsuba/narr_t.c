#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <math.h>
#include "narr_t.h"

#define TRUE_NA_CMP 1
#define FALSE_NA_CMP 0


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

// creates a zero-value numarray_t*
numarray_t* zero_na() {
   numarray_t* t = malloc(sizeof(numarray_t));
   if (!t) {
      return NULL;
   }

   t->num = malloc(sizeof(int)*1);
   if(!t->num) {
      free_na(t);
      return NULL;
   }

   t->num[0] = 0;
   t->len = 1;
   return t;
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

   numarray_t* res = malloc(sizeof(numarray_t));
   res->num = malloc(sizeof(int)*(t->len + n));
   if (res == NULL) {
      DEBUG_OUTPUT("Returning NULL from padl_na, malloc failed.\n");
      return NULL;
   }

   if (n == 0) {
      memcpy(res->num, t->num, t->len*sizeof(int)); // THIS IS CAUSING SEGFAULT
      res->len=t->len;
      printf("Returning early from padl_na, n was 0.\n");
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

// Equalizes the padding in clones and return the clones, so it does not break trimming.
numarray_t** padeqs_na(numarray_t* a, numarray_t* b) {
   if (!a || !b || !a->num || !b->num) {
      return NULL;
   }

   numarray_t** result = malloc(sizeof(numarray_t*)*2);
   numarray_t* clone_a = clone_na(a);
   if (clone_a == NULL) {
      free(result);
      return NULL;
   }

   numarray_t* clone_b = clone_na(b);
   if (clone_b == NULL) {
      free_na(clone_a);
      free(result);
      return NULL;
   }

   padeq_na(clone_a, clone_b);
   result[0] = clone_a;
   result[1] = clone_b;
   return result;
}

// Takes a numarray_t* and modifies _in place_ so the amount of digits is a power of 2
numarray_t* padpow2_na(numarray_t* t) {
   double len = (double) t->len;
   double srlen = sqrt(len);
   double nextPow2 = ceil(srlen);
   int desiredLength = (int) pow(nextPow2, 2.0);
   int lengthOffset = desiredLength - t->len;
   return padr_na(t, lengthOffset);
}

/**********************/
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


/*
   CONVERSION FUNCTIONS
*/

char* natstr(numarray_t* t) {
   char* result = malloc(sizeof(char)*(t->len+1));
   if (result == NULL) {
      return NULL;
   }

   int chidx = 0;
   for (int i = t->len-1; i >= 0; i--) {
      result[chidx++] = t->num[i]+'0';
   }

   result[chidx] = '\0';
   return result;
}


/*
   HELPER FUNCTIONS
*/

int iszero_na(numarray_t* t) {
   if (t == NULL || t->num == NULL) {
      return 0;
   }

   for(int i = 0; i < t->len; i++){
      if (t->num[i] != 0) {
         return 0;
      }
   }
   return 1;
}

/*
   COMPARE FUNCTIONS
*/

/*
   COMPARE FUNCTIONS
*/

int eq_na(numarray_t* a, numarray_t* b) {
   if (!(a) && !(b)) {
      return TRUE_NA_CMP; // if both are null, they are equal
   }

   if(!(a) || !(b)) { //only one of them is NULL
      return FALSE_NA_CMP; // they are not equal;
   }

   numarray_t* c_a = clone_na(a);
   numarray_t* c_b = clone_na(b);
   trim_na(c_a);
   trim_na(c_b);

   if (c_a->len != c_b->len) {
      free_na(c_a);
      free_na(c_b);
      return FALSE_NA_CMP;
   }

   free_na(c_a);
   free_na(c_b);

   if (!a->num && !b->num) {
      return TRUE_NA_CMP;
   }

   if (!a->num || !b->num) {
      return FALSE_NA_CMP;
   }

   c_a = clone_na(a);
   c_b = clone_na(b);

   padeq_na(c_a, c_b);

   for (int i = c_a->len - 1; i > 0; i--) {
      if (c_a->num[i] != c_b->num[i]) {
         free_na(c_a);
         free_na(c_b);
         return FALSE_NA_CMP;
      }
   }

   free_na(c_a);
   free_na(c_b);
   return TRUE_NA_CMP;
}

// a > b ? 1 : 0
int gt_na(numarray_t* a, numarray_t* b) {
   if (!(a) && !(b)) {
      return FALSE_NA_CMP; // if both are null, they are equal
   }

   if(!(a) || !(b)) { //only one of them is NULL
      return FALSE_NA_CMP; // they are not equal;
   }

   if (!a->num && !b->num) {
      return FALSE_NA_CMP;
   }

   if (!a->num || !b->num) {
      return FALSE_NA_CMP;
   }

   numarray_t* c_a = clone_na(a);
   numarray_t* c_b = clone_na(b);
   padeq_na(c_a, c_b);

   int gt = 0;
   for(int i = c_a->len - 1; i > 0; i--) {
      if (c_a->num[i] == c_b->num[i]) {
         continue;
      } else {
         gt =  c_a->num[i] > c_b->num[i];
         break;
      }
   }

   free_na(c_a);
   free_na(c_b);
   return gt;
}
int ge_na(numarray_t* a, numarray_t* b) {
   return gt_na(a, b) || eq_na(a, b);
}

int lt_na(numarray_t* a, numarray_t* b) {
   // Included to avoid returning true when ge returns false based on nullity.

   if (!(a) && !(b)) {
      return FALSE_NA_CMP; // if both are null, they are equal
   }

   if(!(a) || !(b)) { //only one of them is NULL
      return FALSE_NA_CMP; // they are not equal;
   }

   if (!a->num && !b->num) {
      return FALSE_NA_CMP;
   }

   if (!a->num || !b->num) {
      return FALSE_NA_CMP;
   }

   return !ge_na(a, b);
}

int le_na(numarray_t* a, numarray_t* b) {
   return lt_na(a, b) || eq_na(a, b);
}
int ne_na(numarray_t* a, numarray_t* b) {
   return !eq_na(a, b);
}

/*
   ASSERTION FUNCTIONS
*/

int asserteq_na(numarray_t* a, numarray_t* b, char* msg_s, char* msg_f) {
   if (eq_na(a, b)) {
      printf("[ASSERT_EQ SUCCESS, (%s) == (%s)]> %s\n", natstr(a), natstr(b), msg_s ? msg_s : "no_msg");
      return TRUE_NA_CMP;
   }

   printf("[ASSERT_EQ FAILED, (%s) != (%s)]> %s\n", natstr(a), natstr(b), msg_f ? msg_f : "no_msg");
   return FALSE_NA_CMP;
}