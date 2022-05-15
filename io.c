/*
 * io.c
 * Riešenie IJC-DU2, príklad 2), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include "io.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//funckia pre čítanie slova zo súboru
int read_word(char *s, int max, FILE *f) {
    //overenie správnosti súboru
    if (f == NULL) {
        fprintf(stderr, "Chyba v otváraní súboru!\n");
        return -1;
    }
    
    int count = 0;
    int c = fgetc(f);
    //ukladanie jednotlivých písmen do stringu
    while (c != EOF) {
        if (isspace(c)) {
            s[count] = '\0';
            if (!strcmp(s, "\0")) {
                c = fgetc(f); 
                continue;
            }
            return count;
        } else {
            s[count] = c;
            count++;
        }

        //ak slovo prekročí maximálnu dĺžku
        if (count == (max-1)) {
            s[count] = '\0';
            return count;
        }
        c = fgetc(f); 
    }
    return EOF;
}
