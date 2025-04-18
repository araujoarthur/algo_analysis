# GALlib

Implementação de uma lista dinâmica (lista com arranjo) genérica em C.

>[!IMPORTANT]
>É obrigatória a utilização do compilador GCC por conta do macro `__typeof__`.

## Operações

- [X] Criar a lista (`gal_create`)
- [X] Expansão condicional de capacidade (`__gal_requires_resize` e `__gal_expand`)
- [X] Adicionar elemento (`gal_append`)
- [X] Adicionar elemento genérico (`gml_append`)
- [X] Obter elemento em determinado índice (`gal_getn`)
- [X] Obter elemento genérico em determinado índice (`gml_getn`)
- [X] Adicionar elemento em determinado indice (`gal_insert_at`)
- [X] Adicionar elemento genérico em determinado indice (`gml_insert_at`).
- [X] Remover último elemento (`gal_pop`)
- [X] Remover último elemento genérico (`gml_pop`)
- [X] Definir valor de elemento em determinado índice (`gal_setn`)
- [X] Definir valor de elemento genérico em determinado índice (`gml_setn`)
- [ ] Remover elemento em índice determinado (`gal_dropn`)
- [ ] Remover elemento genérico em índice determinado (`gml_dropn`)
- [ ] Buscar indice de elemento (`gal_search`).
- [ ] Buscar indice de elemento genérico (`gml_search`)
- [ ] Buscar sequência de elementos (`gal_lookup`)
- [ ] Buscar sequência de elementos genéricos (`gml_lookup`)
