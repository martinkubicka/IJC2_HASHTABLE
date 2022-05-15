/*
 * htab_free.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

//funkcia na uvoľnenie alokovaného miesta tabuľky
void htab_free(htab_t *t) {
    htab_clear(t);
    free(t->ptr_arr);
    free(t);
}
