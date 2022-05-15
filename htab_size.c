/*
 * htab_bucket_size.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"

//funckcia na zistenie počtu uložených prvkov
size_t htab_size(const htab_t * t) {
    return t->size;
}
