/*
 * wordcount.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include "io.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_LEN 127

#ifdef HASHTEST
//hash funkcia djb2 prebratá z: http://www.cse.yorku.ca/~oz/hash.html 
size_t htab_hash_function(htab_key_t str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}
#endif

//funkcia na vypísanie kľúčov a hodnôt tabuľky
void print(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
}

int main(int argc, char *argv[]) {
    //vytvorenie tabuľky o veľkosti prvočísla
    //prvočíslo zvolené kvôli shlukovaniu dát
    //zvolil som väčšie prvočíslo, pretože funkcia resize je náročná
    htab_t *t = htab_init(9973); 
    if (t == NULL) {
        fprintf(stderr, "Chyba vytváranie pola!\n");
        exit(1);
    }
    FILE *file = NULL;
    //ak je zadaný súbor
    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "Chyba otvárania súboru!\n");
            htab_free(t);
            exit(1);
        }
    //získanie vstupu zo stdin
    } else {
        file = stdin;
    }
    
    //získanie jednotlivých slov
    char string[MAX_LEN];
    int ret = read_word(string, MAX_LEN, file);

    //pridanie slov do tabuľky
    htab_pair_t *tmpPair;
    while (ret != EOF) {
        tmpPair = htab_lookup_add(t, string);
        if (tmpPair == NULL) {
            fprintf(stderr, "Chyba pridávanie kľúča!\n");
            htab_free(t);
            exit(1);
        }
        //zvyšovanie počtu výskytu slova
        tmpPair->value = tmpPair->value + 1;
        ret = read_word(string, 100, file);
    }
    //definovanie funkcie na vypísanie hodôt
    htab_for_each(t, print);

    if (file != stdin) { 
        fclose(file);
    }
    htab_free(t);
}
