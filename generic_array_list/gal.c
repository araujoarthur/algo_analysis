#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "gal.h"

/*
 * Responsável pela criação de uma array list genérica
*/
gal_t create_gal(size_t element_size, int element_count) {
    void* element_p = malloc(element_size * element_count);
    
    if (!element_p) {
        return (gal_t){.elements = NULL, .element_size = 0, .element_count = 0};
    }
    
    return (gal_t){element_p, element_size, element_count};
    
}

/*
 * Aqui eu basicamente estou tratando o meu membro `elements` como um blob de memória e usando o alias RAW_MEMORY_OFFSET
 * para realizar aritimética e descobrir onde o novo valor deve ser colocado. Este alias é util porque o tipo void* tem tamanho de 4 bytes, mas não há
 * quaçquer garantia em relação ao tamanho do elemento. Ao utilizar o alias (que por baixo é um char*), consigo garantir que a aritimética será realizada
 * em um ponteiro cujo tamanho final é 1 byte, e isso é suficiente para deslocar corretamente para a posição final.
 * */
pgal_t append_to(pgal_t gal, void* element)
{
    if (!gal || !element) {
        return NULL;
    }

    void* new_mem_block = realloc(gal->elements, gal->element_size * (gal->element_count + 1));
    if (!new_mem_block) return NULL;

    gal->elements = new_mem_block;
    
    void* val_pos = (RAW_MEMORY_OFFSET)gal->elements + gal->element_size * gal->element_count;
    memcpy(val_pos, element, gal->element_size);

    return gal;

}
