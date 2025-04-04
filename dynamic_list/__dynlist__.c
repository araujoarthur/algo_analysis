#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "__dynlist__.h"

#define ENSURE_ENOUGH_SIZE(l)     \
    do{                           \
      if (l->top >= l->len - 1) { \
        resize_list(l);           \
      }                           \   
    }while(0)                     \

    //do{}while(0) is used as scope protection. (see linux kernel, for instance)

#define ENSURE_POSITIVE(i)                \
    do{                                   \
      if (i < 0) {                        \
        fprintf(stderr, "f** you\n");     \
        system("shutdown -h now");         \
        exit(EXIT_FAILURE);               \
      }                                   \
    }while(0)                             \

la_t* NewList(void) {
  la_t* l = malloc(sizeof(la_t*));
  if (l == NULL) {
    return NULL;
  }
  

  l->len = 2;
  l->list = malloc(sizeof(int)*l->len);
  if (l->list == NULL) {
    return NULL;
  }

  l->top = 0;

  return l;
}

// Frees the inner tracker the list pointer itself.
void TerminateList(la_t* l) {
  if (l == NULL) {
    return;
  }

  if (!(l->list == NULL)) {
    free(l->list);
  }

  free(l);
}

// Adds an item to the last index.
void AddLastItem(la_t* l, int n) {
  ENSURE_ENOUGH_SIZE(l);

  l->list[l->top++] = n;
  return;
}

// Adds an item to an index.
void AddToIndex(la_t* l, int n, int i) {
  ENSURE_POSITIVE(i);
  
  if (l == NULL) {
    return;
  }

  if (i >= l->top) { // Avoiding overhead if inserting on the last item.
    AddLastItem(l, n);
    return;
  }

  ENSURE_ENOUGH_SIZE(l);

  if (!forward_shift(l, i)) { // Not possible to return false yet, but safeguarding
    return;
  }

  l->list[i] = n;

  return;
}

// Gets the item on a index; Returns -1 if the item is not there
int GetFromIndex(la_t* l, int i) {
  if (l == NULL) {
    return -1;
  }
  ENSURE_POSITIVE(i);
  
  if (l->top <= i) {
    return -1;
  }

  return l->list[i];
}

// Sets the value on a given index.
void SetAtIndex(la_t* l, int n, int i) {
  if (l == NULL) {
    return;
  }

  ENSURE_POSITIVE(i);

  if (i >= l->top) {
    return;
  }

  l->list[i] = n;
  return;
}

// Removes the item form an index.
void Remove(la_t* l, int i) {
  if (l == NULL) {
    return;
  }

  ENSURE_POSITIVE(i);
  backward_shift(l, i);
}

// Checks if the list is empty.
boolean_t IsEmpty(la_t* l) {
  return (l != NULL) && (l->top > 0);
}

// Return the amount of items in the list.
int ListSize(la_t* l) {
  if (l == NULL) {
    return 0;
  }
  return l->top;
}

// Checks if the list contains n
boolean_t ListContains(la_t* l, int n) { // Ideally this one should wrap IndexOfOnList, but as mine returns -1 and -1 can or cannot be present on the list...
  if (l == NULL) {
    return False;
  }

  for(int i = 0; i < l->top; i++) {
    if (l->list[i] == n) {
      return True;
    }
  }

  return False;
}

// Returns the index of N if on list, -1 if not found.
int IndexOfOnList(la_t* l, int n) {
  if (l == NULL) {
    return -1;
  }

  for(int i = 0; i < l->top; i++) {
    if (l->list[i] == n) {
      return i;
    }
  }

  return -1;
}

// Removes all elements of the list.
void ListClear(la_t* l, int n) {
  if (l == NULL) {
    return;
  }

  if (l->list != NULL){
    free(l->list);
  }

  l->len = 2;
  l->top = 0;
  l->list = malloc(sizeof(int) * l->len);
}


// Helper List Interface //

// Doubles the size of a list and returns the list itself.
boolean_t resize_list(la_t* l) {
  int* temporary = l->list;
  l->len *= 2;

  l->list = malloc(sizeof(int)*l->len);
  if (l->list == NULL) {
    l->list = temporary;
    l->len /= 2;
    return False;
  }

  memcpy(l->list, temporary, sizeof(temporary)*l->top);
  return True;
}


// Shifts the array starting from 'f' to the end; (Essentially, empties the slot f).
// It assumes the array has enough space to shift.
// BAD THINGS WILL HAPPEN IF THE IMPLEMENTER FAILS THIS ASSUMPTION.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
boolean_t forward_shift(la_t* l, int f) {
  memmove(&l->list[f+1], &l->list[f], sizeof(int)*(l->top - f));
  l->top++;
  return True;
}

/*
The same behavior would be accomplished by:

boolean_t forward_shift(la_t* l, int f) {
  for(int i = l->top++; i >= f; i--) { // This ++ on l->top really really really isn't necessary, buuuut it's neat ;)
    l->list[i+1] = l->list[i]; // 
  }

  return True;
}
return;
*/

// Shifts the array starting from end to 'f'. (Essentially, occupies the slot f).
boolean_t backward_shift(la_t* l, int b) {
  memmove(&l->list[b], &l->list[b+1], sizeof(int) * (l->top -b));
  l->top--;
  return True;
}

void print_list_debug_data(la_t* l) {
  printf("List Max Size: %d\n", l->len);
  printf("List Size: %d\n", ListSize(l));
  printf("List Empty: %s", IsEmpty(l) == True ? "True" : "False");
  printf("List Members:\n");
  for(int i = 0; i < ListSize(l); ++i) {
    printf("List[%d] = %d\n", i, l->list[i]);
  }
  printf("\n\n");
}



int main() {
  printf("Test\n");
  la_t* test = NewList();
  
  if (test != NULL) {
    printf("Successful List Allocation!\n");
    print_list_debug_data(test);
    AddLastItem(test, 10); // 0
    print_list_debug_data(test);
    AddLastItem(test, 20); // 1
    print_list_debug_data(test);
    AddLastItem(test, 30); // 2
    print_list_debug_data(test);
    AddLastItem(test, 13); // 3
    print_list_debug_data(test);
    AddLastItem(test, 22); // 4
    print_list_debug_data(test);
    AddLastItem(test, 31); // 5
    print_list_debug_data(test);
    AddLastItem(test, 19); // 6
    print_list_debug_data(test);
    AddLastItem(test, 24); // 7
    print_list_debug_data(test);
    AddLastItem(test, 37); // 8
    print_list_debug_data(test);

    printf("\nInsertion to Index: \n");
    AddToIndex(test, 99, 3);
    print_list_debug_data(test);


    printf("List Contains 31: %s\n", ListContains(test, 31) == True ? "True" : "False");
    printf("\nRemoving from Index: 6 \n");
    printf("Current Item: %d\n", GetFromIndex(test, 6));
    Remove(test, 6);
    printf("After Remove Item: %d\n", GetFromIndex(test, 6));
    printf("List Contains 31: %s\n", ListContains(test, 31) == True ? "True" : "False");

    print_list_debug_data(test);

    printf("List Contains 19: %s\n", ListContains(test, 19) == True ? "True" : "False");

  }


  return 0;
}

