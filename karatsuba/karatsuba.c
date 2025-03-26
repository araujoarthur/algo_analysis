#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "narr_t.h"
#include "narr_t_maths.h"
#include "karatsuba.h"


int karatsuba_executions = 0;
int node_id = 0;
int node_ind = 2;

char* createIndent(int n, char m) {
   char* ch = malloc(sizeof(char)*((2*n)+1));
   if (ch == NULL) {
      return NULL;
   }

   for (int i = 0; i < (n)-2; i += 2) {
      ch[i]=m;
      ch[i+1]=' ';
   }

   ch[(2*n)-1] = '>';
   ch[(2*n)] ='\0';
   return ch;
}

#define INDENTNODE_CHAR '|'

//#define PRINT_TREE

#ifdef PRINT_TREE
   #define PRINT_NODE(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define PRINT_NODE(fmt, ...) ((void)0)
#endif

/* THIS DOCS IS OUTDATED.
TODO: REWRITE THIS DOCUMENTATION
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
numarray_t** splem_na(numarray_t* t, int cut) {
   if(t == NULL){
      return NULL;
   }

   numarray_t** res = malloc(sizeof(numarray_t*)*2);
   if (res == NULL) {
      return NULL;
   }

   int higher_len = HCT(t, cut);
   int lower_len = LCT(t, cut);

   numarray_t* a = malloc(sizeof(numarray_t));
   numarray_t* b = malloc(sizeof(numarray_t));

   if (!a || !b) {
      free_na(a);
      free_na(b);
      free(res);
      return NULL;
   }

   a->len = higher_len;
   b->len = lower_len;

   a->num = malloc(sizeof(int)*higher_len);
   b->num = malloc(sizeof(int)*lower_len);
   if (!a->num || !b->num) {
      free_na(a);
      free_na(b);
      free(res);
      return NULL;
   }

   memcpy(a->num, t->num+cut, sizeof(int)*higher_len);
   memcpy(b->num, t->num, sizeof(int)*lower_len);

   res[0] = b;
   res[1] = a;

   return res;
}

numarray_t* karatsuba(numarray_t* num_a, numarray_t* num_b){
   int stack_level_node_id = node_id++;
   int stack_level_node_ind = node_ind;
   node_ind += 2;

   if (!num_a || !num_b || !num_a->num || !num_b->num) {
      return NULL;
   }

   PRINT_NODE("%s\n", createIndent(stack_level_node_ind, INDENTNODE_CHAR));
   PRINT_NODE("%s[SPAWN NODE-ID %d] Entered Karatsuba With num_a = %s ; num_b = %s\n", createIndent(stack_level_node_ind, INDENTNODE_CHAR), stack_level_node_id, natstr(num_a), natstr(num_b));

   numarray_t** padded = padeqs_na(num_a, num_b);
   numarray_t* cln_a = padded[0];
   numarray_t* cln_b = padded[1];
   free(padded);

   PRINT_NODE("%s[NODE-ID %d | DEPTH: %d] Created Clones: cln_a: %s ; cln_b = %s\n", createIndent(stack_level_node_ind+1, INDENTNODE_CHAR), stack_level_node_id, node_id, natstr(cln_a), natstr(cln_b));
 

   if ((cln_a->len == 1 && cln_b->len == 1)) { // I assume both will be size 1 because I only consider inputs that have power of two length
      int result = cln_a->num[0] * cln_b->num[0];
      numarray_t* res_na_t = splint_na(result);
      PRINT_NODE("%sNode %d Returned as Base Case %s\n", createIndent(stack_level_node_ind, INDENTNODE_CHAR), stack_level_node_id, natstr(res_na_t));
      return res_na_t;
   }

   if (iszero_na(cln_a) || iszero_na(cln_b)) {
      return zero_na();
   }

   int cutIdx;
   cutIdx = cln_a->len/2;

   //printf("(%d) Already Equally Padded? %s | %s \n", cutIdx, natstr(cln_a), natstr(cln_b));
   numarray_t** x = splem_na(cln_a, cutIdx);
   if(x == NULL) {
      return NULL;
   }

   numarray_t** y = splem_na(cln_b, cutIdx);
   if (y == NULL) {
      free_na(x[0]);
      free_na(x[1]);
      return NULL;
   }

   int cutBasis = HCT(cln_a, cutIdx);

   numarray_t* b = x[0];
   numarray_t* a = x[1];

   numarray_t* d = y[0];
   numarray_t* c = y[1];

   //printf(">>>Selected b(%s), a(%s), c(%s), d(%s)\n", natstr(a), natstr(b), natstr(c), natstr(d));
   
   //printf("a = %s, b = %s | a + b = ?\n", natstr(a), natstr(b));
   numarray_t* p = sum_na(a, b);
   //printf("a = %s, b = %s | a + b = %s\n\n", natstr(a), natstr(b), natstr(p));
  // printf("c = %s, d = %s | c + d = ?\n", natstr(c), natstr(d));
   numarray_t* q = sum_na(c, d);
  // printf("c = %s, d = %s | c + d = %s\n", natstr(c), natstr(d), natstr(q));
 
   PRINT_NODE("%s[NODE-ID %d | DEPTH: %d] (Pre-AC) Going Recursive(%d) on ac | a = %s ; c = %s\n", createIndent(stack_level_node_ind+1, INDENTNODE_CHAR), stack_level_node_id, node_id, stack_level_node_id+1, natstr(a), natstr(c));
   numarray_t* ac = karatsuba(a, c);
   PRINT_NODE("%s[NODE-ID %d | DEPTH: %d] (AC Performed) Received Return from Karatsuba(%d) | a = %s ; c = %s | ac: %s\n", createIndent(stack_level_node_ind+1, INDENTNODE_CHAR), stack_level_node_id, node_id, stack_level_node_id+1, natstr(a), natstr(c), natstr(ac));

   PRINT_NODE("%s[NODE-ID %d | DEPTH: %d] (Pre-BD) Going Recursive(%d) on bd| b = %s ; d = %s\n", createIndent(stack_level_node_ind+1, INDENTNODE_CHAR), stack_level_node_id, node_id, stack_level_node_id+1, natstr(b), natstr(d));
   numarray_t* bd = karatsuba(b, d);
   PRINT_NODE("%s[NODE-ID %d | DEPTH: %d] (BD Performed) Received Return from Karatsuba(%d) | b = %s ; d = %s | bd: %s\n", createIndent(stack_level_node_ind+1, INDENTNODE_CHAR), stack_level_node_id, node_id, stack_level_node_id+1, natstr(b), natstr(d), natstr(bd));

   PRINT_NODE("%s[NODE-ID %d | DEPTH: %d] (Pre-PQ) Going Recursive(%d) on pq | p = %s ; q = %s\n", createIndent(stack_level_node_ind+1, INDENTNODE_CHAR), stack_level_node_id, node_id, stack_level_node_id+1, natstr(p), natstr(q));
   numarray_t* pq = karatsuba(p, q);
   PRINT_NODE("%s[NODE-ID %d | DEPTH: %d] (PQ Performed) Received Return from Karatsuba(%d) | p = %s ; q = %s | pq: %s\n", createIndent(stack_level_node_ind+1, INDENTNODE_CHAR), stack_level_node_id, node_id, stack_level_node_id+1, natstr(p), natstr(q), natstr(pq));

   numarray_t* acbd = sum_na(ac, bd);
   // proceed to subtraction
   
   numarray_t* adbc = subtract_na(pq, acbd); // pq - (ac + bd)

   int padFactor = 2*(_MAX(num_a->len/2, 1)); // Derives the padding factor (the n on Bˆn) from the lenght of A given len(cln_a) == len(cln_b)

   PRINT_NODE("padFactor (%d), padFactor/2 (%d) ---- %s * 10^%d + %s * 10^%d + %s\n", padFactor, padFactor/2, natstr(ac), padFactor, natstr(adbc), padFactor/2, natstr(bd));

   
   numarray_t* paddedAC = padl_na(ac, padFactor);

   numarray_t* paddedADBC = padl_na(adbc, padFactor/2);
  
   PRINT_NODE("ac*10ˆ%d = %s | adbc*10ˆ%d%s\n", padFactor, natstr(paddedAC), padFactor/2, natstr(paddedADBC));
   numarray_t* intermediary_sum = sum_na(paddedAC, paddedADBC);
   numarray_t* result = sum_na(intermediary_sum, bd);
   //terminateNumArray(intermediary_sum);
   //terminateNumArray(z0);

   // should I free num_a and num_b and return only the result?
   PRINT_NODE("%sNode %d Returned %s(%zu)\n", createIndent(stack_level_node_id, INDENTNODE_CHAR), stack_level_node_id, natstr(result), result->len);
   return trim_na(result);
}

