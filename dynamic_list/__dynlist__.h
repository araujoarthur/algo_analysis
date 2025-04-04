#pragma once

typedef struct LA {
  int* list;
  int len;
  int top; // The next index to be inserted.
} la_t;

typedef enum BOOLEAN {
  False,
  True
} boolean_t;


// Public list interface //

// Gets memory for a new list LA.
la_t* NewList(void);

// Frees the inner tracker the list pointer itself.
void TerminateList(la_t* l);

// Adds an item to the last index.
void AddLastItem(la_t* l, int n);

// Adds an item to an index.
void AddToIndex(la_t* l, int n, int i);

// Gets the item on a index; Returns -1 if the item is not there
int GetFromIndex(la_t* l, int i);

// Sets the value on a given index.
void SetAtIndex(la_t* l, int n, int i);

// Removes the item form an index.
void Remove(la_t* l, int i);

// Checks if the list is empty.
boolean_t IsEmpty(la_t* l);

// Return the amount of items in the list.
int ListSize(la_t* l);

// Checks if the list contains n
boolean_t ListContains(la_t* l, int n);

// Returns the index of N if on list, -1 if not found.
int IndexOfOnList(la_t* l, int n);

// Removes all elements of the list.
void ListClear(la_t* l, int n);


// Helper List Interface //

// Doubles the size of a list and returns the list itself.
boolean_t resize_list(la_t* l);

// Shifts the array starting from 'f' to the end; (Essentially, empties the slot f).
boolean_t forward_shift(la_t* l, int f);

// Shifts the array starting from end to 'f'. (Essentially, occupies the slot f).
boolean_t backward_shift(la_t* l, int b);