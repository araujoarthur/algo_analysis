#include <stdlib.h>
#include <stdio.h>
#include "simple_testf.h"
#include "narr_t.h"
#include "narr_t_maths.h"
#include "karatsuba.h"

int tc_id = 0;

test_ctx* create_test_ctx() {
   test_ctx* ctx = malloc(sizeof(test_ctx));
   ctx->success = 0;
   ctx->failed = 0;
   ctx->ran = 0;

   return ctx;
}

tc_k_t create_tck(char* name, char* desc, char* x, char* y, char* expected) {
   tc_k_t tc;
   tc.id = tc_id++;
   tc.x = crfch_na(x);
   tc.y = crfch_na(y);
   tc.expected = crfch_na(expected);
   tc.name = name;
   tc.description = desc;

   return tc;
}

void freemembers_tck(tc_k_t test) {
   if (test.x) {
      free_na(test.x);
   }

   if (test.y) {
      free_na(test.y);
   }

   if (test.expected) {
      free_na(test.expected);
   }

   if (test.result) {
      free_na(test.result);
   }

   if (test.name) {
      free(test.name);
   }

   if(test.description) {
      free(test.description);
   }

   return;
}


void run_tck(tc_k_t test, test_ctx* ctx) {
   printf("---------------------------------------------------------------------------------------------------\n");
   printf("--> Runing Test Case: %d                                                                          ██\n", test.id);
   printf("---------------------------------------------------------------------------------------------------\n");
   ctx->ran++;
   printf("|   TEST NAME: %s\n|\n", test.name);
   printf("|   TEST DESCRIPTION: \n|    %s\n", test.description);
   printf("|\n");
   printf("|   ▒▒▒▒▒▒▒▒▒▒▒▒\n");
   printf("|▒▒▒▒  INPUTS  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█\n");
   printf("|   ▒▒▒▒▒▒▒▒▒▒▒▒\n|\n");
   printf("|     x:\t%s\n", natstr(test.x));
   printf("|     y:\t%s\n", natstr(test.y));
   printf("|\n");
   printf("|   ▒▒▒▒▒▒▒▒▒▒▒▒\n");
   printf("|▒▒▒▒  OUTPUT  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█\n");
   printf("|   ▒▒▒▒▒▒▒▒▒▒▒▒\n|\n");
   test.result = karatsuba(test.x, test.y);
   printf("|     x (after):\t%s\n", natstr(test.x));
   printf("|     y (after):\t%s\n", natstr(test.y));
   printf("|\n");
   printf("|     RESULT:\t%s\n", natstr(test.result));
   printf("|       LEN:\t%zu\n|\n", test.result->len);
   printf("|     EXPECTED:\t%s\n", natstr(test.expected));
   printf("|       LEN:\t%zu\n", test.expected->len);
   printf("|\n");
   printf("|   ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");
   printf("|▒▒▒▒  ASSERTIONS  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█\n");
   printf("|   ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n|\n");
   if (asserteq_na(test.expected, test.result, "Result is the expected value.", "Result is not the expected value.")) {
      ctx->success++;
   } else {
      ctx->failed++;
      //printliml_na(test.result->num, test.result->len);
      //dump_na(test.result);
      //exit(0);
   }
   //TODO

   printf("═══════════════════════════════════════════════════════════════════════════════════════════════════\n");
   printf("<-- Finished Test Case: %d                                                                         █\n", test.id);
   printf("═══════════════════════════════════════════════════════════════════════════════════════════════════\n\n");
   return;
}