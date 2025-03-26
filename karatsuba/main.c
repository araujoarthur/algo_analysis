#include <stdio.h>
#include "narr_t.h"
#include "narr_t_maths.h"
#include "karatsuba.h"


int main() {
   numarray_t* in1 = crfch_na("3141592653589793238462643383279502884197169399375105820974944592");
   printn_na(in1);
   numarray_t* in2 = crfch_na("2718281828459045235360287471352662497757247093699959574966967627");
   printn_na(in2);

   printf("\n\n\nKARATSUBA TEST\n\n\n");
   numarray_t* mult_test2 = crfch_na("3141592653589793238462643383279502884197169399375105820974944592");
   numarray_t* mult_test1 = crfch_na("2718281828459045235360287471352662497757247093699959574966967627");
   //numarray_t* karatsuba_1_2 = karatsuba(mult_test1, mult_test2);
   printf("25x15 = ");
   NUMARRAY_T_DUMP("karatsuba_1_2", "main", karatsuba_1_2);
   //printn_na(karatsuba_1_2);
   printf("...\n");
   //numarray_t* t1 = crfch_na("102");
   //numarray_t* t2 = crfch_na("108");
   //numarray_t* wow = karatsuba(t1, t2);
   
   numarray_t* t3 = crfch_na("205");
   numarray_t* t4 = crfch_na("100");
   numarray_t* t5 = crfch_na("00000");
   
   numarray_t* wow = karatsuba(t3, t4);

   //numarray_t** t3 = splem_na()
   return 0;
}
