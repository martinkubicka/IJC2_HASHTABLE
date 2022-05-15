/*
 * htab_bucket_count.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"

//funkcia na zistenie veľkosti pola
size_t htab_bucket_count(const htab_t * t) {
    return t->arr_size;
}
