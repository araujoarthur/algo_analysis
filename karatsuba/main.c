#include <stdio.h>
#include "narr_t.h"
#include "narr_t_maths.h"
#include "karatsuba.h"
#include "simple_testf.h"

#define TEST_COUNT 83

void do_general_tests() {
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
      "Interval Multiplication 6 digits",
      "Multiply two numbers of 6 digits",
      "123456",
      "123456",
      "15241383936");

   tests[18] = create_tck(
      "Interval Multiplication 7 digits",
      "Multiply two numbers of 7 digits",
      "1234567",
      "1234567",
      "1524155677489");

   tests[19] = create_tck(
      "Interval Multiplication 8 digits",
      "Multiply two numbers of 8 digits",
      "12345678",
      "12345678",
      "152415765279684");

   tests[20] = create_tck(
      "Interval Multiplication 9 Digits",
      "Multiply two numbers of 9 digits",
      "123456789",
      "123456789",
      "15241578750190521");

   tests[21] = create_tck(
      "Interval Multiplication 10 digits",
      "Multiply two numbers of 10 digits",
      "1234567890",
      "1234567890",
      "1524157875019052100");
   
   tests[22] = create_tck(
      "Interval Multiplication 11 digits",
      "Multiply two numbers of 11 digits",
      "12345678901",
      "12345678901",
      "152415787526596567801");
   
   tests[23] = create_tck(
      "Interval Multiplication 12 digits",
      "Multiply two numbers of 12 digits",
      "123456789012",
      "123456789012",
      "15241578753153483936144");
   
   tests[24] = create_tck(
      "Interval Multiplication 13 digits",
      "Multiply two numbers of 13 digits",
      "1234567890123",
      "1234567890123",
      "1524157875322755800955129");

   tests[25] = create_tck(
      "Interval Multiplication 14 digits",
      "Multiply two numbers of 14 digits",
      "12345678901234",
      "12345678901234",
      "152415787532374345526722756");
   
   tests[26] = create_tck(
      "Interval Multiplication 15 digits",
      "Multiply two numbers of 15 digits",
      "123456789012345",
      "123456789012345",
      "15241578753238669120562399025");
   
   tests[27] = create_tck(
      "Interval Multiplication 16 digits",
      "Multiply two numbers of 16",
      "1234567890123456",
      "1234567890123456",
      "1524157875323881726870921383936");
   
   tests[28] = create_tck(
      "Interval Multiplication 17 digits",
      "Multiply two numbers of 17 digits",
      "12345678901234567",
      "12345678901234567",
      "152415787532388345526596755677489");
   
   tests[29] = create_tck(
      "Interval Multiplication 18 digits",
      "Multiply two numbers of 18 digits",
      "123456789012345678",
      "123456789012345678",
      "15241578753238836527968299765279684");

   tests[30] = create_tck(
      "Interval Multiplication 19 digits",
      "Multiply two numbers of 19 digits",
      "1234567890123456789",
      "1234567890123456789",
      "1524157875323883675019051998750190521");
      
   tests[31] = create_tck(
      "Interval Multiplication 20 digits",
      "Multiply two numbers of 20 digits",
      "12345678901234567890",
      "12345678901234567890",
      "152415787532388367501905199875019052100");

   tests[32] = create_tck(
      "Interval Multiplication 21 digits",
      "Multiply two numbers of 21 digits",
      "123456789012345678901",
      "123456789012345678901",
      "15241578753238836750437433565526596567801");

   tests[33] = create_tck(
      "Interval Multiplication 22 digits",
      "Multiply two numbers of 22 digits",
      "1234567890123456789012",
      "1234567890123456789012",
      "1524157875323883675048681628113153483936144");
   
   tests[34] = create_tck(
      "Interval Multiplication 23 digits",
      "Multiply two numbers of 23 digits",
      "12345678901234567890123",
      "12345678901234567890123",
      "152415787532388367504942236884722755800955129");

   tests[35] = create_tck(
      "Interval Multiplication 24 digits",
      "Multiply two numbers of 24 digits",
      "123456789012345678901234",
      "123456789012345678901234",
      "15241578753238836750495211342784374345526722756");

   tests[36] = create_tck(
      "Interval Multiplication 25 digits",
      "Multiply two numbers of 25 digits",
      "1234567890123456789012345",
      "1234567890123456789012345",
      "1524157875323883675049533479957338669120562399025");

   tests[37] = create_tck(
      "Interval Multiplication 26 digits",
      "Multiply two numbers of 26 digits",
      "12345678901234567890123456",
      "12345678901234567890123456",
      "152415787532388367504953496143880681726870921383936");

   tests[38] = create_tck(
      "Interval Multiplication 27 digits",
      "Multiply two numbers of 27 digits",
      "123456789012345678901234567",
      "123456789012345678901234567",
      "15241578753238836750495351342783114345526596755677489");

   tests[39] = create_tck(
      "Interval Multiplication 28 digits",
      "Multiply two numbers of 28 digits",
      "1234567890123456789012345678",
      "1234567890123456789012345678",
      "1524157875323883675049535154031397676527968299765279684");

   tests[40] = create_tck(
      "Interval Multiplication 29 digits",
      "Multiply two numbers of 29 digits",
      "12345678901234567890123456789",
      "12345678901234567890123456789",
      "152415787532388367504953515625361987875019051998750190521");

   tests[41] = create_tck(
      "Interval Multiplication 30 digits",
      "Multiply two numbers of 30 digits",
      "123456789012345678901234567890",
      "123456789012345678901234567890",
      "15241578753238836750495351562536198787501905199875019052100");

   tests[42] = create_tck(
      "Interval Multiplication 31 digits",
      "Multiply two numbers of 31 digits",
      "1234567890123456789012345678901",
      "1234567890123456789012345678901",
      "1524157875323883675049535156256089014530437433565526596567801");

   tests[43] = create_tck(
      "Interval Multiplication 32 digits",
      "Multiply two numbers of 32 digits",
      "12345678901234567890123456789012",
      "12345678901234567890123456789012",
      "152415787532388367504953515625658284168648681628113153483936144");

   tests[43] = create_tck(
      "Interval Multiplication 33 digits",
      "Multiply two numbers of 33 digits",
      "123456789012345678901234567890123",
      "123456789012345678901234567890123",
      "15241578753238836750495351562566569157598942236884722755800955129");

   tests[44] = create_tck(
      "Interval Multiplication 34 digits",
      "Multiply two numbers of 34 digits",
      "1234567890123456789012345678901234",
      "1234567890123456789012345678901234",
      "1524157875323883675049535156256666792303015211342784374345526722756");

   tests[45] = create_tck(
      "Interval Multiplication 35 digits",
      "Multiply two numbers of 35 digits",
      "12345678901234567890123456789012345",
      "12345678901234567890123456789012345",
      "152415787532388367504953515625666802687090533479957338669120562399025");

   tests[46] = create_tck(
      "Interval Multiplication 36 digits",
      "Multiply two numbers of 36 digits",
      "123456789012345678901234567890123456",
      "123456789012345678901234567890123456",
      "15241578753238836750495351562566681750190521496143880681726870921383936");

   tests[47] = create_tck(
      "Interval Multiplication 37 digits",
      "Multiply two numbers of 37 digits",
      "1234567890123456789012345678901234567",
      "1234567890123456789012345678901234567",
      "1524157875323883675049535156256668192303002611342783114345526596755677489");

   tests[48] = create_tck(
      "Interval Multiplication 38 digits",
      "Multiply two numbers of 38 digits",
      "12345678901234567890123456789012345678",
      "12345678901234567890123456789012345678",
      "152415787532388367504953515625666819427831123554031397676527968299765279684");

   tests[49] = create_tck(
      "Interval Multiplication 39 digits",
      "Multiply two numbers of 39 digits",
      "123456789012345678901234567890123456789",
      "123456789012345678901234567890123456789",
      "15241578753238836750495351562566681945005334557625361987875019051998750190521");

   tests[50] = create_tck(
      "Interval Multiplication 40 digits",
      "Multiply two numbers of 40 digits",
      "1234567890123456789012345678901234567890",
      "1234567890123456789012345678901234567890",
      "1524157875323883675049535156256668194500533455762536198787501905199875019052100");

   tests[51] = create_tck(
      "Interval Multiplication 41 digits",
      "Multiply two numbers of 41 digits",
      "12345678901234567890123456789012345678901",
      "12345678901234567890123456789012345678901",
      "152415787532388367504953515625666819450078036934056089014530437433565526596567801");

   tests[52] = create_tck(
      "Interval Multiplication 42 digits",
      "Multiply two numbers of 42 digits",
      "123456789012345678901234567890123456789012",
      "123456789012345678901234567890123456789012",
      "15241578753238836750495351562566681945008297520561658284168648681628113153483936144");

   tests[53] = create_tck(
      "Interval Multiplication 43 digits",
      "Multiply two numbers of 43 digits",
      "1234567890123456789012345678901234567890123",
      "1234567890123456789012345678901234567890123",
      "1524157875323883675049535156256668194500837159463506569157598942236884722755800955129");

   tests[54] = create_tck(
      "Interval Multiplication 44 digits",
      "Multiply two numbers of 44 digits",
      "12345678901234567890123456789012345678901234",
      "12345678901234567890123456789012345678901234",
      "152415787532388367504953515625666819450083814711781866792303015211342784374345526722756");

   tests[55] = create_tck(
      "Interval Multiplication 45 digits",
      "Multiply two numbers of 45 digits",
      "123456789012345678901234567890123456789012345",
      "123456789012345678901234567890123456789012345",
      "15241578753238836750495351562566681945008382705746076802687090533479957338669120562399025");

   tests[56] = create_tck(
      "Interval Multiplication 46 digits",
      "Multiply two numbers of 46 digits",
      "1234567890123456789012345678901234567890123456",
      "1234567890123456789012345678901234567890123456",
      "1524157875323883675049535156256668194500838285389422361750190521496143880681726870921383936");

   tests[57] = create_tck(
      "Interval Multiplication 47 digits",
      "Multiply two numbers of 47 digits",
      "12345678901234567890123456789012345678901234567",
      "12345678901234567890123456789012345678901234567",
      "152415787532388367504953515625666819450083828711781740792303002611342783114345526596755677489");

   tests[58] = create_tck(
      "Interval Multiplication 48 digits",
      "Multiply two numbers of 48 digits",
      "123456789012345678901234567890123456789012345678",
      "123456789012345678901234567890123456789012345678",
      "15241578753238836750495351562566681945008382873153482703427831123554031397676527968299765279684");

   tests[59] = create_tck(
      "Interval Multiplication 49 digits",
      "Multiply two numbers of 49 digits",
      "1234567890123456789012345678901234567890123456789",
      "1234567890123456789012345678901234567890123456789",
      "1524157875323883675049535156256668194500838287337570492365005334557625361987875019051998750190521");

   tests[60] = create_tck(
      "Interval Multiplication 50 digits",
      "Multiply two numbers of 50 digits",
      "12345678901234567890123456789012345678901234567890",
      "12345678901234567890123456789012345678901234567890",
      "152415787532388367504953515625666819450083828733757049236500533455762536198787501905199875019052100");

   tests[61] = create_tck(
      "Interval Multiplication 51 digits",
      "Multiply two numbers of 51 digits",
      "123456789012345678901234567890123456789012345678901",
      "123456789012345678901234567890123456789012345678901",
      "15241578753238836750495351562566681945008382873375951837228078036934056089014530437433565526596567801");

   tests[62] = create_tck(
      "Interval Multiplication 52 digits",
      "Multiply two numbers of 52 digits",
      "1234567890123456789012345678901234567890123456789012",
      "1234567890123456789012345678901234567890123456789012",
      "1524157875323883675049535156256668194500838287337600121994368297520561658284168648681628113153483936144");

   tests[63] = create_tck(
      "Interval Multiplication 53 digits",
      "Multiply two numbers of 53 digits",
      "12345678901234567890123456789012345678901234567890123",
      "12345678901234567890123456789012345678901234567890123",
      "152415787532388367504953515625666819450083828733760086273510237159463506569157598942236884722755800955129");

   tests[64] = create_tck(
      "Interval Multiplication 54 digits",
      "Multiply two numbers of 54 digits",
      "123456789012345678901234567890123456789012345678901234",
      "123456789012345678901234567890123456789012345678901234",
      "15241578753238836750495351562566681945008382873376009615005335814711781866792303015211342784374345526722756");

   tests[65] = create_tck(
      "Interval Multiplication 55 digits",
      "Multiply two numbers of 55 digits",
      "1234567890123456789012345678901234567890123456789012345",
      "1234567890123456789012345678901234567890123456789012345",
      "1524157875323883675049535156256668194500838287337600973846212482705746076802687090533479957338669120562399025");

   tests[66] = create_tck(
      "Interval Multiplication 56 digits",
      "Multiply two numbers of 56 digits",
      "12345678901234567890123456789012345678901234567890123456",
      "12345678901234567890123456789012345678901234567890123456",
      "152415787532388367504953515625666819450083828733760097532769395085389422361750190521496143880681726870921383936");

   tests[67] = create_tck(
      "Interval Multiplication 57 digits",
      "Multiply two numbers of 57 digits",
      "123456789012345678901234567890123456789012345678901234567",
      "123456789012345678901234567890123456789012345678901234567",
      "15241578753238836750495351562566681945008382873376009755005334554711781740792303002611342783114345526596755677489");

   tests[68] = create_tck(
      "Interval Multiplication 58 digits",
      "Multiply two numbers of 58 digits",
      "1234567890123456789012345678901234567890123456789012345678",
      "1234567890123456789012345678901234567890123456789012345678",
      "1524157875323883675049535156256668194500838287337600975520286541713153482703427831123554031397676527968299765279684");

   tests[69] = create_tck(
      "Interval Multiplication 59 digits",
      "Multiply two numbers of 59 digits",
      "12345678901234567890123456789012345678901234567890123456789",
      "12345678901234567890123456789012345678901234567890123456789",
      "152415787532388367504953515625666819450083828733760097552250876391537570492365005334557625361987875019051998750190521");

   tests[70] = create_tck(
      "Interval Multiplication 60 digits",
      "Multiply two numbers of 60 digits",
      "123456789012345678901234567890123456789012345678901234567890",
      "123456789012345678901234567890123456789012345678901234567890",
      "15241578753238836750495351562566681945008382873376009755225087639153757049236500533455762536198787501905199875019052100");

   tests[71] = create_tck(
      "Interval Multiplication 61 digits",
      "Multiply two numbers of 61 digits",
      "1234567890123456789012345678901234567890123456789012345678901",
      "1234567890123456789012345678901234567890123456789012345678901",
      "1524157875323883675049535156256668194500838287337600975522511233051155951837228078036934056089014530437433565526596567801");

   tests[72] = create_tck(
      "Interval Multiplication 62 digits",
      "Multiply two numbers of 62 digits",
      "12345678901234567890123456789012345678901234567890123456789012",
      "12345678901234567890123456789012345678901234567890123456789012",
      "152415787532388367504953515625666819450083828733760097552251172687831200121994368297520561658284168648681628113153483936144");

   tests[73] = create_tck(
      "Interval Multiplication 63 digits",
      "Multiply two numbers of 63 digits",
      "123456789012345678901234567890123456789012345678901234567890123",
      "123456789012345678901234567890123456789012345678901234567890123",
      "15241578753238836750495351562566681945008382873376009755225118009523854086273510237159463506569157598942236884722755800955129");

   tests[74] = create_tck(
      "Interval Multiplication 64 digits",
      "Multiply two numbers of 64 digits",
      "1234567890123456789012345678901234567890123456789012345678901234",
      "1234567890123456789012345678901234567890123456789012345678901234",
      "1524157875323883675049535156256668194500838287337600975522511810828928529615005335814711781866792303015211342784374345526722756");

   tests[75] = create_tck(
      "Interval Multiplication 65 digits",
      "Multiply two numbers of 65 digits",
      "12345678901234567890123456789012345678901234567890123456789012345",
      "12345678901234567890123456789012345678901234567890123456789012345",
      "152415787532388367504953515625666819450083828733760097552251181206349641973846212482705746076802687090533479957338669120562399025");

   tests[76] = create_tck(
      "Interval Multiplication 65 digits per inverse",
      "Multiply two numbers of 65 digits by the same number but inverted",
      "54321098765432109876543210987654321098765432109876543210987654321",
      "12345678901234567890123456789012345678901234567890123456789012345",
      "670630842920274332577348558086266968291479908077433311932571863267642052215515919900426763457930193492581771063937052277861592745");

   tests[77] = create_tck(
      "Interval Multiplication 64 digits per inverse",
      "Multiply two numbers of 64 digits b",
      "1234567890123456789012345678901234567890123456789012345678901234",
      "4321098765432109876543210987654321098765432109876543210987654321",
      "5334689785854593807117571863564968434641817968292713909312124599603655838835537051771070851965858799875461051455433622292332114");

   tests[78] = create_tck(
      "Interval Multiplication 63 digits",
      "Multiply two numbers of 63 digits",
      "321098765432109876543210987654321098765432109876543210987654321",
      "123456789012345678901234567890123456789012345678901234567890123",
      "39641822536076665106818914796003016308132414113666452659651966231926077710709754559822690134857440481373261194926077834171483");

   tests[79] = create_tck(
      "Interval Multiplication 62 digits per inverse",
      "Multiply two numbers of 62 digits",
      "12345678901234567890123456789012345678901234567890123456789012",
      "21098765432109876543210987654321098765432109876543210987654321",
      "260478583237296143644854442896597927142871040999608228928492926862978141438012493018972717189414418507693156529644487120852");
   
   tests[80] = create_tck(
      "Interval Multiplication 61 digits per inverse",
      "Multiply two numbers of 61 digits by the same number inverted",
      "1234567890123456789012345678901234567890123456789012345678901",
      "1098765432109876543210987654321098765432109876543210987654321",
      "1356500521260478584238530711635101356484634964180575979271268466544727721825940659699740854721688764347340344322251181221");

   tests[81] = create_tck(
      "Interval Multiplication 60 digits per inverse",
      "Multiply two numbers of 60 digits by the same number inverted",
      "123456789012345678901234567890123456789012345678901234567890",
      "098765432109876543210987654321098765432109876543210987654321",
      "12193263113702179522618503273386678859451150739156363359236736777929561194939744871208653362292333223746380111126352690");

   tests[82] = create_tck(
      "Interval Multiplication 59 digits per inverse",
      "Multiply two numbers of 59 digits by the same number inverted",
      "98765432109876543210987654321098765432109876543210987654321",
      "12345678901234567890123456789012345678901234567890123456789",
      "1219326311370217952261850327338667885945115073915636335923673677792956119493974487120865336229233322374638011112635269");

   test_ctx* tctx = create_test_ctx();

   for(int i = 0; i < TEST_COUNT; i++) {
      run_tck(tests[i], tctx);
   }

   
   printf("Tests Finished. A total of %d tests were ran, %d succeeded and %d failed", tctx->ran, tctx->success, tctx->failed);   
}


int main() {
   numarray_t* in1 = crfch_na("3141592653589793238462643383279502884197169399375105820974944592");
   printn_na(in1);
   numarray_t* in2 = crfch_na("2718281828459045235360287471352662497757247093699959574966967627");
   printn_na(in2);

   //do_general_tests();

   numarray_t *critical1 = crfch_na("123456789012");
   numarray_t *critical2 = crfch_na("123456789012");
   numarray_t *critical_res = karatsuba(critical1, critical2);
   printf("Critical Result: %s\nResult of printn_na (result): ", natstr(critical_res));
   printn_na(critical_res);
   printf("\nResult of printn_na (critical1):\n");
   printn_na(critical1);
   printf("\nResult of printn_na (critical2):\n");
   printn_na(critical2);
   //numarray_t* wow = karatsuba(in1, in2);
   //printf("Result Len: %zu | Value: %s\n", wow->len, natstr(wow));
   return 0;
}
