#include <stdio.h>
#include "narr_t.h"
#include "narr_t_maths.h"
#include "karatsuba.h"


int main() {
   char* inputNumber1 = "3141592653589793238462643383279502884197169399375105820974944592";
   char* inputNumber2 = "2718281828459045235360287471352662497757247093699959574966967627";
   
   numarray_t* in1 = crfch_na(inputNumber1);
   printliml_na(in1->num, in1->len);
   numarray_t* in2 = crfch_na(inputNumber2);
   printliml_na(in2->num, in2->len);

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
