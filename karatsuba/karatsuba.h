#pragma once

#include "narr_t.h"
#include "narr_t_maths.h"

#define DEBUGGING
//#define DUMPING


numarray_t* karatsuba(numarray_t* num_a, numarray_t* num_b);
numarray_t** splem_na(numarray_t* t, int n);