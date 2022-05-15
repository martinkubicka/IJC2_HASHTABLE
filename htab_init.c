/*
 * htab_init.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"
#include <stdio.h>
#include <stdlib.h>

//funkcia na vytvorenie hashovacej tabuľky o veľkosti n
htab_t *htab_init(size_t n) {
    htab_t *tab = malloc(sizeof(htab_t));
    if (tab == NULL) {
        return NULL;
    }
    tab->ptr_arr = malloc(n*sizeof(htab_item_t*));
    if (tab->ptr_arr == NULL) {
        return NULL;
    } else {
        tab->size = 0;
        tab->arr_size = n;
        for (size_t i = 0; i < n; i++) {
            tab->ptr_arr[i] = NULL;
        }
    }
    return tab;
} 
