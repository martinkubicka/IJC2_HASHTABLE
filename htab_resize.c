/*
 * htab_resize.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//funkcia na zmenu veľkosti (newn) tabuľky 
void htab_resize(htab_t *t, size_t newn) {
    //vytvorenie novej tabuľky pre uchovanie potrebných dát
    htab_t *tmp = htab_init(htab_bucket_count(t));
    if (tmp == NULL) {
        fprintf(stderr, "Chyba vytvárania tabuľky!\n");
        exit(1);
    }
    tmp->arr_size = t->arr_size;
    //prekopírovanie kľúčov a hodnôt do tabuľky tmp
    for (size_t i = 0; i < htab_bucket_count(t); i++) {
        for (htab_item_t *tmp1 = t->ptr_arr[i]; tmp1 != NULL; tmp1 = tmp1->next) {
            htab_pair_t *tmp_pair = htab_lookup_add(tmp, tmp1->pair->key);
            if (tmp_pair == NULL) {
                fprintf(stderr, "Chyba pridávanie kľúča!\n");
                exit(1);
            }
            tmp_pair->value = tmp1->pair->value;
        }
    }
    //vymazanie kľúčov a dát z tabuľky zadanej uživateľom
    htab_clear(t);
    //vytvorenie pola o novej veľkosti
    t->ptr_arr = realloc(t->ptr_arr, newn*sizeof(htab_item_t*));
    t->arr_size = newn;
    if (t->ptr_arr != NULL) {
        //nakopírovanie kľúčov a hodnôt z tabuľky tmp do tabuľky zadanej uživateľom
        for (size_t i = 0; i < htab_bucket_count(tmp); i++) {
            for (htab_item_t *tmp1 = tmp->ptr_arr[i]; tmp1 != NULL; tmp1 = tmp1->next) {
                htab_pair_t *tmp_pair = htab_lookup_add(t, tmp1->pair->key);
                if (tmp_pair == NULL) {
                    fprintf(stderr, "Chyba pridávanie kľúča!\n");
                    exit(1);  
                }
                tmp_pair->value = tmp1->pair->value;
            }
        }   
        htab_free(tmp); 
    } else {
        //alokácia zlyhala -> zachovanie pôvodnej tabuľky
        htab_clear(t);
        t->ptr_arr = tmp->ptr_arr;   
    }
}
