/*
 * htab_find.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"
#include <string.h>

//funckia na nájdenie kľúča v tabuľke
htab_pair_t *htab_find(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    //hľadanie kľúča
    if (t->ptr_arr[index] != NULL) {
            for (htab_item_t *tmp = t->ptr_arr[index]; tmp != NULL; tmp = tmp->next) {
                if(!strcmp(tmp->pair->key, key)) {
                    return tmp->pair;
                }
            }
            //kľúč nenájdený
            return NULL;
    //kľúč nenájdený
    } else {
        return NULL;
    }
}
