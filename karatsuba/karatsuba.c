#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void printNumArray(int* numArray, int count);

// Holds the number reversed. So idx 0 is 10ˆ0, idx 1 is 10ˆ1 and so on.
typedef struct NUMARRAY {
   int* num;
   size_t len;
} numarray_t;

// Free a numarray_t
void* terminateNumArray(numarray_t* t) {
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

/*
The summation will not work if they don't have the same amount of digits.
I present ya: PADDING!

padr pads with zero's to the right of the memory layout
*/
numarray_t* padr_na(numarray_t* t, size_t howMuch) {
   if (t == NULL) {
      return NULL;
   }

   int* ret = realloc(t->num, sizeof(int)*(t->len + howMuch));
   if (ret == NULL) {
      return NULL;
   }

   t->num = ret;
   memset(&t->num[t->len], 0, howMuch*sizeof(int));

   t->len += howMuch;
   return t;
}

// Guess what it does? Pads to the left of the memory layout
numarray_t* padl_na(numarray_t* t, size_t howMuch) {
   
   return NULL;
}

// Takes a pointer to numarray_t, removes all leading zeros (to the right in memory layout)
// Returns t without trailling zeros and with the correct length.
numarray_t* trim_na(numarray_t* t) {
   if (t == NULL || t->num == NULL) {
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
      return NULL;
   }

   t->num = new_num;
   t->len = newlen;

   return t;
}

// Equalizes the digit length between a and b by adding 0's to the beginning of the one with the smaller length.
void EqualizePadding(numarray_t* a, numarray_t* b) {
   if (a == NULL || b == NULL) {
      return;
   }

   if(a->len == b->len) {
      return;
   }

   if(a->len > b->len) {
      padr_na(b, a->len - b->len);
      return;
   }

   padr_na(a, b->len - a->len);
   return;
}

numarray_t* createEmptyNumArray(int amount){
   numarray_t* result = malloc(sizeof(numarray_t));
   if (result == NULL) {
      return NULL;
   }

   result->len = 0; // Yes, zero. The user can set it later
   result->num = malloc(sizeof(int)*amount);
   if (result->num == NULL) {
      free(result);
      return NULL;
   }

   return result;
}

// creates a new numarray_t from a string
numarray_t* createArrayFromChar(char* inp) {
   numarray_t* nt = malloc(sizeof(numarray_t));
   if (nt == NULL) {
      return NULL;
   }

   nt->len = strlen(inp);
   nt->num = malloc(sizeof(int) * nt->len);
   if (nt->num == NULL) {
      free(nt);
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
      return NULL;
   }

   numarray_t* clone = malloc(sizeof(numarray_t));
   if (clone == NULL) {
      return NULL;
   }

   clone->len = a->len;
   clone->num = malloc(sizeof(int)*clone->len);
   if (clone->num == NULL) {
      terminateNumArray(clone);
   }

   memcpy(clone->num, a->num, sizeof(int)*clone->len);
   return clone;
}

// Splits an integer into a numarray_t
numarray_t* splitNumberIntoArray(int i) {
   int digitAmount = ((int) log10((double) i)) + 1;
   
   numarray_t* nt = malloc(sizeof(numarray_t));
   if (nt == NULL) {
      return NULL;
   }

   nt->num = malloc(sizeof(int)*digitAmount);
   if (nt->num == NULL) {
      free(nt);
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
numarray_t** splitElements(numarray_t* t, int n) {
   numarray_t** res = malloc(sizeof(numarray_t*)*2);
   if (res == NULL) {
      return NULL;
   }

   res[0] = malloc(sizeof(numarray_t));
   if (res[0] == NULL) {
      free(res);
      return NULL;
   }

   res[1] = malloc(sizeof(numarray_t));
   if (res[1] == NULL) {
      free(res[0]);
      free(res);
      return NULL;
   }

   res[0]->len = n;
   res[1]->len = n;

   res[0]->num = malloc(sizeof(int) * res[0]->len);
   if (res[0]->num == NULL) {
      free(res[0]);
      free(res[1]);
      free(res);
      return NULL;
   }

   res[1]->num = malloc(sizeof(int)*res[1]->len);
   if (res[1]->num == NULL) {
      free(res[0]->num);
      free(res[0]);
      free(res[1]);
      free(res);
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
   int carry = 0;
   numarray_t* result = createEmptyNumArray(a->len+b->len);

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
      return NULL;
   }

   result->num = r;

   return result;
}

// Performs the subtraction a - b (subtracts b from a)
// This function has the assumption that a-b is still a positive number.
numarray_t* subtract_na(numarray_t* a, numarray_t* b) {
   EqualizePadding(a, b);

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
      exit(EXIT_FAILURE);
   }

   return trim_na(result);
}


numarray_t* karatsuba(numarray_t* num_a, numarray_t* num_b){
   if (num_a == NULL || num_b == NULL) {
      return NULL;
   }

   EqualizePadding(num_a, num_b);

   if (num_a->len == 1 && num_b->len == 1) { // I assume both will be size 1 because I only consider inputs that have power of two length
      int result = num_a->num[0] * num_b->num[0];
      numarray_t* res_na_t = splitNumberIntoArray(result);
      //Should I free num_a and num_b and return only the result?
      return res_na_t;
   }

   int new_n;
   new_n = (num_a->len > num_b->len ? num_b->len : num_a->len)/2;
   numarray_t** x = splitElements(num_a, new_n);
   if(x == NULL) {
      return NULL;
   }

   numarray_t** y = splitElements(num_b, new_n);
   if (y == NULL) {
      terminateNumArray(x[0]);
      terminateNumArray(x[1]);
      return NULL;
   }

   numarray_t* x0 = x[0];
   numarray_t* x1 = x[1];

   numarray_t* y0 = y[0];
   numarray_t* y1 = y[1];

   numarray_t* sum_x = sum_na(x[0], x[1]);
   numarray_t* sum_y = sum_na(y[0], y[1]);

   numarray_t* z0 = karatsuba(x[0], y[0]);
   numarray_t* z2 = karatsuba(x[1], y[1]);

   EqualizePadding(sum_x, sum_y);
   numarray_t* z3 = karatsuba(sum_x, sum_y);

   // proceed to subtraction
   numarray_t* z1 = subtract_na(z3, z2);
   z1 = subtract_na(z1, z0);

   // pad left each zn accordingly, add them, return the result of the addition.
   // should I free num_a and num_b and return only the result?
   return NULL;
}

int main() {
   char* inputNumber1 = "3141592653589793238462643383279502884197169399375105820974944592";
   char* inputNumber2 = "2718281828459045235360287471352662497757247093699959574966967627";
   
   numarray_t* in1 = createArrayFromChar(inputNumber1);
   printNumArray(in1->num, in1->len);
   numarray_t* in2 = createArrayFromChar(inputNumber2);
   printNumArray(in2->num, in2->len);
   numarray_t* in3 = splitNumberIntoArray(123445);
   printNumArray(in3->num, in3->len);
   numarray_t** split = splitElements(in2, in2->len/2);
   if (split == NULL) {
      printf("Split failed.\n");
   }


   numarray_t* testSum1 = createArrayFromChar("2");
   printNumArray(testSum1->num, testSum1->len);
   numarray_t* testSum2 = createArrayFromChar("3");
   printNumArray(testSum2->num, testSum2->len);
   numarray_t* summation = sum_na(testSum1, testSum2);
   printNumArray(summation->num, summation->len);
   printf("\n\n\n\n");

   numarray_t* testPad1 = createArrayFromChar("234521");
   numarray_t* testPad2 = createArrayFromChar("244");
   printf("testPad1: ");
   printNumArray(testPad1->num, testPad1->len);
   printf("testPad2: ");
   printNumArray(testPad2->num, testPad2->len);

   EqualizePadding(testPad1, testPad2);

   printf("Equalized testPad1: ");
   printNumArray(testPad1->num, testPad1->len);
   printf("Equalized testPad2: ");
   printNumArray(testPad2->num, testPad2->len);

   // TRIM TESTS

   printf("\n\n\n\n");
   printf("Trim Test Test\n");
   numarray_t* nothing_to_trim = createArrayFromChar("200");
   numarray_t* one_zero_to_trim = createArrayFromChar("01000");
   numarray_t* multiple_zero_to_trim = createArrayFromChar("000103420");
   printf("nothing_to_trim: ");
   printNumArray(nothing_to_trim->num, nothing_to_trim->len);

   printf("one_zero_to_trim: ");
   printNumArray(one_zero_to_trim->num, one_zero_to_trim->len);

   printf("multiple_zero_to_trim: ");
   printNumArray(multiple_zero_to_trim->num, multiple_zero_to_trim->len);

   printf("\ntrimming\n");

   numarray_t* nothing_to_trim_trimmed = trim_na(nothing_to_trim);
   numarray_t* one_zero_to_trim_trimmed = trim_na(one_zero_to_trim);
   numarray_t* multiple_zero_to_trim_trimmed = trim_na(multiple_zero_to_trim);

   printf("nothing_to_trim_trimmed: ");
   printNumArray(nothing_to_trim_trimmed->num, nothing_to_trim_trimmed->len);

   printf("one_zero_to_trim_trimmed: ");
   printNumArray(one_zero_to_trim_trimmed->num, one_zero_to_trim_trimmed->len);

   printf("multiple_zero_to_trim_trimmed: ");
   printNumArray(multiple_zero_to_trim_trimmed->num, multiple_zero_to_trim_trimmed->len);


   printf("\n\n\n\n");
   printf("Subtraction Test\n");
   numarray_t* testSubtrA = createArrayFromChar("288");
   printNumArray(testSubtrA->num, testSubtrA->len);
   numarray_t* testSubtrB = createArrayFromChar("199");
   printNumArray(testSubtrB->num, testSubtrB->len);

   numarray_t* subtractionAfter = subtract_na(testSubtrA, testSubtrB);
   printNumArray(subtractionAfter->num, subtractionAfter->len);

   numarray_t* tsA = createArrayFromChar("2888");
   numarray_t* tsB = createArrayFromChar("999");
   numarray_t* tsC = createArrayFromChar("100");
   numarray_t* tsD = createArrayFromChar("10");
   
   numarray_t* stepped_subtraction = subtract_na(tsA, tsB);
   printf("Stepped Subtraction Step 1 (EXPECTED 1889 [9,8,8,1]): ");
   printNumArray(stepped_subtraction->num, stepped_subtraction->len);

   stepped_subtraction = subtract_na(stepped_subtraction, tsC);
   printf("Stepped Subtraction Step 2 (EXPECTED 1789 [9,8,7,1]): ");
   printNumArray(stepped_subtraction->num, stepped_subtraction->len);

   stepped_subtraction = subtract_na(stepped_subtraction, tsD);
   printf("Stepped Subtraction Step 3 (EXPECTED 1789 [9,7,7,1]): ");
   printNumArray(stepped_subtraction->num, stepped_subtraction->len);

   return 0;
}

