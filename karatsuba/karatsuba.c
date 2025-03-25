#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void printNumArray(int* numArray, int count);

#define DEBUGGING
//#define DUMPING

#ifdef DUMPING
   #define NUMARRAY_T_DUMP(F, A, T) \
      do { \
         printf("\n=============Object Dump for %s @ %s===============\n", F, A);\
         printf("%s's Address: %p\n", F, &T);\
         printf("%s's Pointee: %p\n", F, (void*)T);\
         if(T==NULL){ \
            printf("T IS NULL \n");\
            printf("\n=============END DUMP for %s @ %s===============\n", F, A);\
            break; \
         }\
         printf("%s->num Address: %p\n", F, &T->num);\
         printf("%s->num Pointee: %p\n", F, (void*)T->num); \
         printf("%s->len value: %zu\n", F, T->len); \
         printf("%s's numeric value: ", F); \
         for(int ijk = T->len-1; ijk >= 0; ijk--) { \
            printf("%d", T->num[ijk]); \
         }\
         printf("\n=============END DUMP for %s @ %s===============\n", F, A);\ 
      }while(0)
#else
      #define NUMARRAY_T_DUMP(F, A, T) ((void)0)
#endif

#ifdef DEBUGGING
   #define DEBUG_OUTPUT(T) printf(T)
   #define DEBUG_OUTPUT_H(T, U) printf(T, U)

#else
   #define DEBUG_OUTPUT(T) ((void)0)
   #define DEBUG_OUTPUT_H(T, U) ((void)0)
#endif

int karatsuba_executions = 0;

// Holds the number reversed. So idx 0 is 10ˆ0, idx 1 is 10ˆ1 and so on.
typedef struct NUMARRAY {
   int* num;
   size_t len;
} numarray_t;

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

void printn_na(numarray_t* t) {
   if (t == NULL || t->num == NULL) {
      return;
   }
   
   for(int i = t->len-1; i >= 0; i--) {
      printf("%d", t->num[i]);
   }

   printf("\n");
}

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
// it's equivalent to multiplying t*10^howMuch
// returns a different numarray_t*
numarray_t* padl_na(numarray_t* t, size_t howMuch) {
   if (t == NULL || t->num == NULL) {
      DEBUG_OUTPUT("Returning NULL from padl_na, t or t->num was NULL.\n");
      return NULL;
   }

   numarray_t* res = malloc(sizeof(int)*(t->len + howMuch));
   if (res == NULL) {
      DEBUG_OUTPUT("Returning NULL from padl_na, malloc failed.\n");
      return NULL;
   }

   if (howMuch == 0) {
      memcpy(res->num, t->num, t->len*sizeof(int));
      res->len=t->len;
      DEBUG_OUTPUT("Returning early from padl_na, howMuch was 0.\n");
      return res;
   }

   res->num = calloc((t->len + howMuch), sizeof(int));
   if (res->num == NULL) {
      free_na(res);
      DEBUG_OUTPUT("Returning NULL from padl_na, calloc failed.\n");
      return NULL;
   }

   memcpy(&res->num[howMuch], t->num, sizeof(int)*t->len);
   res->len = howMuch + t->len;
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

void printNumArray(int* numArray, int count) {
   for(int n = 0; n < count; n++) {
      printf("%d",numArray[n]);
   }

   printf("\n");
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

int main() {
   char* inputNumber1 = "3141592653589793238462643383279502884197169399375105820974944592";
   char* inputNumber2 = "2718281828459045235360287471352662497757247093699959574966967627";
   
   numarray_t* in1 = crfch_na(inputNumber1);
   printNumArray(in1->num, in1->len);
   numarray_t* in2 = crfch_na(inputNumber2);
   printNumArray(in2->num, in2->len);

   printf("\n\n\nKARATSUBA TEST\n\n\n");
   numarray_t* mult_test2 = crfch_na("3141592653589793238462643383279502884197169399375105820974944592");
   numarray_t* mult_test1 = crfch_na("2718281828459045235360287471352662497757247093699959574966967627");
   numarray_t* karatsuba_1_2 = karatsuba(mult_test2, mult_test1);
   printf("25x15 = ");
   NUMARRAY_T_DUMP("karatsuba_1_2", "main", karatsuba_1_2);
   printn_na(karatsuba_1_2);
   printf("...");
   return 0;
}

