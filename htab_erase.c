/*
 * htab_erase.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//ak size/bucket_count tabuľky bude menšie ako toto číslo tak sa prevedie zmenšenie tabuľky
//po otestovaní mi vyšlo číslo 0.25 najadekvátnejšie kedy zmenšiť tabuľku
#define AVG_LEN_MIN 0.25

//funkcia na vymazanie konkrétneho kľúča
bool htab_erase(htab_t * t, htab_key_t key) {
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    //ak existuje nejaký kľúč na indexe
    if (t->ptr_arr[index] != NULL) {
        int count = 0;
        //premenná na uchovávanie predošlej položky
        htab_item_t *previous;
        //prechod položkami
        for (htab_item_t *tmp = t->ptr_arr[index]; tmp != NULL; tmp = tmp->next) {
            //ak je kľúč nájdený
            if (!strcmp(tmp->pair->key, key)) {
                //ak sa jedná o prvú položku
                if (count == 0) {
                    htab_item_t *store = t->ptr_arr[index];
                    t->ptr_arr[index] = tmp->next; 
                    free((char *)store->pair->key);
                    free(store->pair);
                    free(store);
                } else {
                    //ak sa jedná o poslednú položku
                    if (tmp->next == NULL) {
                        previous->next = NULL;
                        free((char *)tmp->pair->key);
                        free(tmp->pair);
                        free(tmp);
                    //ak sa jedná o položku v strede
                    } else {
                        htab_item_t *store = tmp;
                        previous->next = tmp->next;
                        free((char *)store->pair->key);
                        free(store->pair);
                        free(store);
                    }    
                }
                t->size = t->size - 1;
                return true;
            }
            count++;
            previous = tmp;
        }
        return false;
    } else {
        return false;
    }
}   
