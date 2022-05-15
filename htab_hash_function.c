/*
 * htab_hash_function.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "htab.h"
#include <stdint.h>

//funkcia na vytvorenie hashu pre určitý kľúč
size_t htab_hash_function(htab_key_t str) {
    uint32_t h=0;
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}
