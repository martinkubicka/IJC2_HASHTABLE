/*
 * htab_lookup_add.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <string.h>

//ak size/bucket_count tabuľky presiahne číslo 0.5 tak sa prevedie operácia resize
//pri testovaní mi vyšlo číslo 0.5 najefektívnejšia možnosť kedy zväčšiť tabuľku
#define AVG_LEN_MAX 0.5

//funkcia na pridanie kľúča do tabuľky
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    if (AVG_LEN_MAX < ((double)htab_size(t)/(double)htab_bucket_count(t))) {
        htab_resize(t, htab_bucket_count(t)*2);
    }
    
    //zistenie indexu na ktorý bude kľúč uložený
    size_t index = htab_hash_function(key) % htab_bucket_count(t);

    char *str;

    //ak sa na indexe nenacháza žiaden uložený kľúč
    if (t->ptr_arr[index] == NULL) {
        t->ptr_arr[index] = malloc(sizeof(htab_item_t));
        if (t->ptr_arr[index] == NULL) {
            return NULL;
        }
        t->ptr_arr[index]->pair = malloc(sizeof(htab_pair_t));
        if (t->ptr_arr[index]->pair == NULL) {
            return NULL;
        }
        //skopirovanie kľúča
        str = malloc(strlen(key)*sizeof(htab_key_t));
        if (str == NULL) {
            return NULL;
        }
        strcpy(str, key);
        str[strlen(key)] = '\0';

        t->ptr_arr[index]->pair->key = str;
        t->ptr_arr[index]->pair->value = 0;
        t->ptr_arr[index]->next = NULL;
        t->size = t->size + 1;
        return t->ptr_arr[index]->pair;
    //ak sa na indexe náchádza uložený kľúč
    } else {
        for (htab_item_t *tmp = t->ptr_arr[index]; tmp != NULL; tmp = tmp->next) {
            //ak kľúč existuje v tabuľke
            if (!strcmp(tmp->pair->key, key)){
                return tmp->pair;
            //ak kľúč neexistuje v tabuľke
            } else {
                if (tmp->next == NULL) {
                    tmp->next = malloc(sizeof(htab_item_t));
                    if (tmp->next == NULL) {
                        return NULL;
                    }
                    tmp->next->pair = malloc(sizeof(htab_pair_t));
                    if (tmp->next->pair == NULL) {
                        return NULL;
                    }
                    //skopírovanie kľúča
                    str = malloc(strlen(key)*sizeof(htab_key_t));
                    if (str == NULL) {
                        return NULL;
                    }
                    strcpy(str, key);
                    str[strlen(key)] = '\0';
                    tmp->next->pair->key = str;
                    tmp->next->next = NULL;
                    tmp->next->pair->value = 0;
                    t->size = t->size + 1;
                    return tmp->next->pair;
                }
            }
        }
    }  
    return NULL;
}
