#pragma once
#include <stdlib.h>

/************/
/*  MACROS  */
/************/

#ifdef DUMPING
   #define NUMARRAY_T_DUMP(F, A, T) \
      do { \
         printf("\n=============Object Dump for %s @ %s===============\n", F, A);\
         printf("%s's Address: %p\n", F, &T);\
         printf("%s's Pointee: %p\n", F, (void*)T);\
         if(T==NULL){ \
            printf("T IS NULL \n");\
            printf("\n=============END DUMP for %s @ %s===============\n", F, A);\
            break; \
         }\
         printf("%s->num Address: %p\n", F, &T->num);\
         printf("%s->num Pointee: %p\n", F, (void*)T->num); \
         printf("%s->len value: %zu\n", F, T->len); \
         printf("%s's numeric value: ", F); \
         for(int ijk = T->len-1; ijk >= 0; ijk--) { \
            printf("%d", T->num[ijk]); \
         }\
         printf("\n=============END DUMP for %s @ %s===============\n", F, A);\ 
      }while(0)
#else
      #define NUMARRAY_T_DUMP(F, A, T) ((void)0)
#endif

#ifdef DEBUGGING
   #define DEBUG_OUTPUT(T) printf(T)
   #define DEBUG_OUTPUT_H(T, U) printf(T, U)

#else
   #define DEBUG_OUTPUT(T) ((void)0)
   #define DEBUG_OUTPUT_H(T, U) ((void)0)
#endif

// higher cut limit
#define HCT(T, L) {T->len - L};
#define LCT(T, L) { L };

/* This struct is intended to hold VERY large integers. */
typedef struct NUMARRAY {
   int* num;
   size_t len;
} numarray_t;

/**********************************/
/* Creating and Freeing Functions */
/**********************************/

// creation of an empty numarray_t* with 'amount' memory size in 'numarray_t.num'
numarray_t* cremp_na(int);
// creation of a numarray_t* from a char array (i.e. string).
numarray_t* crfch_na(char*);
// creates a one digit zero numarray_t*
numarray_t* zero_na();
// clone numarray_t* into a new numarray_t*. All fields of the new numarray_t* are independent from the cloned struct.
numarray_t* clone_na(numarray_t*);
// split integer into numarray_t*
numarray_t* splint_na(int i);
// freeing the struct completely 
void* free_na(numarray_t*);

/**********************/
/* PADDING FUNCTIONS */
/*********************/

// padding to the right of the memory layout
numarray_t* padr_na(numarray_t*, size_t);
// padding to the left of the memory layout
numarray_t* padl_na(numarray_t*, size_t);
// leading zeros trimming
numarray_t* trim_na(numarray_t*);
// padding equalization, pads destructively.
void padeq_na(numarray_t*, numarray_t*);
// padding equalization safely, not destructive.
numarray_t** padeqs_na(numarray_t*, numarray_t*);
// pads the numarray_t to the right until its length becomes the next power of 2.
numarray_t* padpow2_na(numarray_t*);


/**********************/
/* PRINTING FUNCTIONS */
/**********************/
// print normal, Displays in the numarray_t number in the expected orientation.
void printn_na(numarray_t*);
// print with limit on layout, i.e prints up to n characters from left to right (memory layout).
void printliml_na(int*, int);


/************************/
/* CONVERSION FUNCTIONS */
/************************/

// numarry_t* to string (char*)
char* natstr(numarray_t*);


/*********************/
/* HELPER FUNCTIONS  */
/*********************/

// verify if the given numarray_t* holds the zero value.
int iszero_na(numarray_t*);
// dumps the actual integer underneath the type
void dump_na(numarray_t* t);

/*
   COMPARE FUNCTIONS
*/

int eq_na(numarray_t* a, numarray_t* b);
int gt_na(numarray_t* a, numarray_t* b);
int ge_na(numarray_t* a, numarray_t* b);
int lt_na(numarray_t* a, numarray_t* b);
int le_na(numarray_t* a, numarray_t* b);
int ne_na(numarray_t* a, numarray_t* b);

/*
   ASSERTION FUNCTIONS
*/

int asserteq_na(numarray_t*, numarray_t*, char*, char*);