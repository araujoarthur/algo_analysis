#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "gal.h"

#define _GAL_P_LAST_ITEM_OFFSET(T) (RAW_MEMORY_OFFSET)T->elements + T->element_count * T->element_size
#define _GAL_P_ELEMENT_POSITION(T, I) (void*)(((RAW_MEMORY_OFFSET)T->elements + I * T->element_size))

/*******************
* OPERATIONS DEFS *
*******************/

/*
* Responsável pela criação de uma array list genérica
*/
gal_t create_gal(size_t element_size, int element_count) {
    int element_cap = 4;
    if (element_count > 0) {
        element_cap = 2 * element_count;
    }

    void* element_p = malloc(element_size * element_cap);
    
    if (!element_p) {
        return (gal_t){.elements = NULL, .element_size = 0, .element_count = 0, .element_cap = 0};
    }
    
    return (gal_t){element_p, element_size, 0, element_cap};
}

/*
 * Aqui eu basicamente estou tratando o meu membro `elements` como um blob de memória e usando o alias RAW_MEMORY_OFFSET
 * para realizar aritimética e descobrir onde o novo valor deve ser colocado. Este alias é util porque o tipo void* tem tamanho de 4 bytes, mas não há
 * quaçquer garantia em relação ao tamanho do elemento. Ao utilizar o alias (que por baixo é um char*), consigo garantir que a aritimética será realizada
 * em um ponteiro cujo tamanho final é 1 byte, e isso é suficiente para deslocar corretamente para a posição final.
 * */
pgal_t gal_append(pgal_t gal, void* element)
{
    if (!gal || !element) {
        return NULL;
    }
    
    // Ensure size.
    if (__gal_requires_resize(gal)) {
        __gal_expand(gal);
    }

    void* val_ptr = _GAL_P_LAST_ITEM_OFFSET(gal);
    memcpy(val_ptr, element, gal->element_size);
    gal->element_count++;
    return gal;
}

void* gal_getn(pgal_t gal, int n) {
    if (!gal || n >= gal->element_count) return NULL;

    void* mem = malloc(gal->element_size*1);
    if (!mem) return NULL;

    memcpy(mem, _GAL_P_ELEMENT_POSITION(gal, n), gal->element_size);
    return mem;
}

/**************
* HELPER DEFS *
***************/

/*
    Apenas verifica se o resize é necessário. Retorna 0 caso não seja, ou n != 0 caso seja.
*/
int __gal_requires_resize(pgal_t gal) {
    return gal->element_cap <= (gal->element_count + 2);
}

/*
    Expande a array. Retorna NULL caso a expansão não funcione, ou o ponteiro para a (estrutura) da array.

    Aqui tem um problema que vale a reflexão no futuro, quando tiver tempo: O realloc vai 
        a) expandir a memória e manter o ponteiro atual ou
        b) mover todo o bloco para uma nova região ou
        c) falhar
    nas opções b) e c) é possível que isso resulte em gal->elements sendo um dangling pointer.
    como posso assegurar que isso NUNCA vai acontecer?
*/
pgal_t __gal_expand(pgal_t gal) {
    int new_cap = gal->element_cap * 2;
    void* new_elems = realloc(gal->elements, gal->element_size * new_cap);
    
    if (!new_elems) {
        // Aqui talvez eu pudesse tentar restaurar a array antiga. Teria que fazer uma _copia_ antes.
        return NULL;
    }

    gal->elements = new_elems;
    gal->element_cap = new_cap;

    return gal;
}