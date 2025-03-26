#include <stdio.h>
#include "narr_t.h"
#include "narr_t_maths.h"
#include "karatsuba.h"
#include "simple_testf.h"

#define TEST_COUNT 31

int main() {
   numarray_t* in1 = crfch_na("3141592653589793238462643383279502884197169399375105820974944592");
   printn_na(in1);
   numarray_t* in2 = crfch_na("2718281828459045235360287471352662497757247093699959574966967627");
   printn_na(in2);

   printf("******************************\n");
   printf("Karatsuba Multiplication Tests\n");
   printf("******************************\n");
   tc_k_t tests[TEST_COUNT];
   tests[0] = create_tck(
      "0 Multiplication",
      "Multiply single digit 0 by 0",
      "0",
      "0",
      "0");

   tests[1] = create_tck(
      "n-digit 0 Multiplication, n is even",
      "Multiply n-digit 0 by 0 with n being even",
      "0000",
      "0000",
      "0");

   tests[2] = create_tck(
      "n-digit 0 Multiplication, n is odd",
      "Multiply n-digit 0 by 0 with n being odd",
      "000",
      "000",
      "0");

   tests[3] = create_tck(
      "n-digi per m-digit 0 Multiplication, n and m are even",
      "Multiply n-digit 0 by m-digit 0 with n and m being even",
      "000000",
      "0000",
      "0");

   tests[4] = create_tck(
      "n-digi per m-digit 0 Multiplication, n is odd, m is even",
      "Multiply n-digit 0 by m-digit 0 with n being odd and m being even",
      "00000",
      "0000",
      "0");
   
   tests[4] = create_tck(
      "n-digi per m-digit 0 Multiplication, n is odd, m is even",
      "Multiply n-digit 0 by m-digit 0 with n being even and m being odd",
      "000000",
      "00000",
      "0");
   
   tests[5] = create_tck(
      "1 digit odd number",
      "Multiply two odd numbers with 1 digit each",
      "5",
      "3",
      "15");
   
   tests[6] = create_tck(
      "1 digit even number",
      "Multiply two even numbers with 1 digit each",
      "4",
      "6",
      "24");
   
   tests[7] = create_tck(
      "1 digit even x odd number",
      "Multiply two numbers with 1 digit each being one even and one odd",
      "4",
      "5",
      "20");
   
   tests[8] = create_tck(
      "2 digit even number",
      "Multiply two even numbers with 2 digit each",
      "40",
      "62",
      "2480");
   
   tests[9] = create_tck(
      "2 digit odd number",
      "Multiply two odd numbers with 2 digit each",
      "41",
      "39",
      "1599");

   tests[10] = create_tck(
      "2 digit even x odd number",
      "Multiply two numbers with 2 digit each, one odd and one even.",
      "46",
      "21",
      "966");

      //
   tests[11] = create_tck(
      "2 digit even x 1 digit even numbers",
      "Multiply two numbers, one even with 2 digit and one even with 1 digit",
      "46",
      "8",
      "368");

   tests[12] = create_tck(
      "1 digit odd x 2 digit odd number",
      "Multiply two numbers, one odd with 2 digit and one odd with 1 digit",
      "7",
      "21",
      "147");
   
   tests[13] = create_tck(
      "2 digit even x 1 digit odd number",
      "Multiply two numbers, one even with 2 digit and one odd with 1 digit",
      "46",
      "3",
      "138");

   tests[14] = create_tck(
      "2 digit odd x 1 digit even number",
      "Multiply two numbers, one odd with 2 digit and one even with 1 digit",
      "45",
      "4",
      "180");

   tests[15] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "3436",
      "21123",
      "72578628");

   tests[16] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "12345",
      "12345",
      "152399025");

   tests[17] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "123456",
      "123456",
      "15241383936");

   tests[18] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "1234567",
      "1234567",
      "1524155677489");

   tests[19] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "12345678",
      "12345678",
      "152415765279684");

   tests[20] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "123456789",
      "123456789",
      "15241578750190521");

   tests[21] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "1234567890",
      "1234567890",
      "1524157875019052100");
   
   tests[22] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "12345678901",
      "12345678901",
      "152415787526596567801");
   
   tests[23] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "123456789012",
      "123456789012",
      "15241578753153483936144");
   
   tests[24] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "1234567890123",
      "1234567890123",
      "1524157875322755800955129");

   tests[25] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "12345678901234",
      "12345678901234",
      "152415787532374345526722756");
   
   tests[26] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "123456789012345",
      "123456789012345",
      "15241578753238669120562399025");
   
   tests[27] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "1234567890123456",
      "1234567890123456",
      "1524157875323881726870921383936");
   
   tests[28] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "12345678901234567",
      "12345678901234567",
      "152415787532388345526596755677489");
   
   tests[29] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "123456789012345678",
      "123456789012345678",
      "15241578753238836527968299765279684");

   tests[30] = create_tck(
      "m-digit x n-digit",
      "Multiply two numbers with different lengths.",
      "1234567890123456789",
      "1234567890123456789",
      "1524157875323883675019051998750190521");
      
   test_ctx* tctx = create_test_ctx();

   for(int i = 0; i < TEST_COUNT; i++) {
      run_tck(tests[i], tctx);
   }

   printf("Tests Finished. A total of %d tests were ran, %d succeeded and %d failed", tctx->ran, tctx->success, tctx->failed);
   //numarray_t* wow = karatsuba(p9, q10);
   //printf("Result Len: %zu | Value: %s\n", wow->len, natstr(wow));
   return 0;
}
