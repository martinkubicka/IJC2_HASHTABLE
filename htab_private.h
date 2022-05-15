/*
 * htab_private.h
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#ifndef __HTAB_PRIVATE_H__
#define __HTAB_PRIVATE_H__

#include "htab.h"

//definícia štruktúry pre položku v poli
typedef struct htab_item {
    htab_pair_t *pair;
    struct htab_item *next;
} htab_item_t;

//definícia štruktúry hashovacej tabuľky
struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t **ptr_arr;
};

#endif // __HTAB_PRIVATE_H__
