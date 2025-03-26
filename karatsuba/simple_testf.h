#pragma once

#include "narr_t.h"

typedef struct TEST_CASE_KARATSUBA {
   int id;
   numarray_t* x;
   numarray_t* y;
   numarray_t* expected;
   numarray_t* result;
   char* name;
   char* description;
} tc_k_t;

typedef struct TESTING_CONTEXT {
   int success;
   int failed;
   int ran;
} test_ctx;

test_ctx* create_test_ctx();
tc_k_t create_tck(char* name, char* desc, char* x, char* y, char* expected);
void run_tck(tc_k_t test, test_ctx* ctx);
void freemembers_tck(tc_k_t test);
