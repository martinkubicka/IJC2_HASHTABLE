/*
 * htab_for_each.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"

//funckia prejde všetký záznamy v tabuľke a na jednotlivé záznamy zavolá funkciu
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0 ; i < t->arr_size; i++) {
        for (htab_item_t *tmp = t->ptr_arr[i]; tmp != NULL ;tmp = tmp->next) {
            (*f)(tmp->pair);
        }
    }
}
