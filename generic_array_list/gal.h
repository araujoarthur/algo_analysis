#pragma once

#include <stdlib.h>

typedef char* RAW_MEMORY_OFFSET;

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

// Cria uma generic array list com capacidade para `element_count` elementos de `element_size` cada.
gal_t create_gal(size_t element_size, int element_count);
// Insere um elemento no final da lista.
pgal_t gal_append(pgal_t gal, void* element);
// Obtem o item encontrado no index n.
void* gal_getn(pgal_t gal, int n);

// Helpers
int __gal_requires_resize(pgal_t gal);
pgal_t __gal_expand(pgal_t gal);

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