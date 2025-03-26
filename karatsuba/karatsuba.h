#pragma once

#include "narr_t.h"
#include "narr_t_maths.h"

#define _MIN(a, b)  a > b ? b : a
#define _MAX(a, b) a > b ? a : b

#define DEBUGGING
//#define DUMPING


numarray_t* karatsuba(numarray_t* num_a, numarray_t* num_b);
numarray_t** splem_na(numarray_t* t, int n);