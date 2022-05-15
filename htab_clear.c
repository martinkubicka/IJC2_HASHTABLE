/*
 * htab_clear.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"

//funkcia na vymazanie všetkých kľúčov
void htab_clear(htab_t * t) {
    for (size_t i = 0 ; i < t->arr_size; i++) {
        while (t->ptr_arr[i] != NULL) {
            htab_erase(t, t->ptr_arr[i]->pair->key);
        }
    }
}
