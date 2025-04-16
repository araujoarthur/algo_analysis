#pragma once

#include <stdlib.h>

typedef char* RAW_MEMORY_OFFSET;
typedef void (*gml_printer_t) (void* element); // Definição de alias p function type.

/*
To-Do: Reimplementar isso só que ao invés de tratar void* como um ponteiro, tratar como um tipo de dados agnostico (e fazer o casting para o tipo concreto quando necessario)
Vai exigir bastante pointer arithmetics, mas é interessante.
*/
typedef struct GenericArrayList {
    void* elements;
    size_t element_size;
    int element_count;
    int element_cap;
} gal_t, *pgal_t;


// Operations

// Cria uma generic array list com capacidade para `element_count` elementos de `element_size` bytes cada.
gal_t gal_create(size_t element_size, int element_count);
// Insere `element` no final da lista.
pgal_t gal_append(pgal_t gal, void* element);
// Obtem o item encontrado no índice `idx`.
void* gal_getn(pgal_t gal, int idx);
// Insere `element` em `gal` na posição `idx` ou na ultima posição, caso idx > element_count;
pgal_t gal_insert_at(pgal_t gal, int idx, void* element);
//

// Helpers
int __gal_requires_resize(pgal_t gal);
pgal_t __gal_expand(pgal_t gal);

// DEFAULT PRINTERS

static void gml_print_int(void* item){ printf("%d", *(int*)item); }
static void gml_print_float(void* item){ printf("%f", *(float*)item); }
static void gml_print_char(void* item){ printf("%c", *(char*)item); }

// GALMHL - GAL Macro Helper Lib

#define _GAL_P_LAST_ITEM_OFFSET(T) (RAW_MEMORY_OFFSET)(T)->elements + (T)->element_count * (T)->element_size

#define _GAL_P_ELEMENT_POSITION(T, I) (void*)(((RAW_MEMORY_OFFSET)(T)->elements + I * (T)->element_size))

#define _GAL_ENSURE_SIZE(T) \
    do {\
        if (__gal_requires_resize(gal)) {\
            __gal_expand(gal);\
        }\
    }while(0)

// GAL (Generic Array List) Macro Lib
// Tem por finalidade tornar mais genérica a utilização da biblioteca.
// Obviamente, os gal macro lib só funciona, dentro de funções.

// Versão genérica de append.
#define gml_append(__gal, __val) \
    do { \
        __typeof__(__val) __gal__tmp = (__val); \
        gal_append((__gal), &__gal__tmp); \
    } while(0)


// Versão genérica de getn
#define gml_getn(__gal, __idx, __dst, __default) \
    do {\
        void* __gotten__ = gal_getn((__gal), (__idx));\
        if (!__gotten__) {\
            *(__dst) = __default;\
        } else {\
            *(__dst) = *(__typeof__(*__dst)*)__gotten__;\
            free(__gotten__);\
        }\
    }while(0)

// Versão genérica de insert_at
#define gml_insert_at(__gal, __idx, __val)\
    do{\
        __typeof__(__val) __gal__tmp = (__val);\
        gal_insert_at((__gal), (__idx), &__gal__tmp);\
    }while(0)

// Mostra a array em stdout de modo formatado.
#define gml_printarr(__gal, __printer_func) \
    do {\
        printf("[");\
        for(int i = 0; i < (__gal)->element_count; i++) {\
            void* el = _GAL_P_ELEMENT_POSITION(__gal, i);\
            if (i != 0) {\
                printf(", ");\
            }\
            __printer_func(el);\
        }\
        printf("]\n");\
    }while(0)


