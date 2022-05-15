/*
 * tail.c
 * Riešenie IJC-DU2, príklad 1), 19.4.2022
 * Autor: Martin Kubička, FIT
 * Preložené: gcc 7.5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struktura na uchovávanie načítaných dát
typedef struct {
    int count; //počítadlo počtu uložených písmen
    int count_lines;
    char *strings_array;
} data_t;

//funkcia na vytvorenie štruktúry
data_t *ctor() {
    data_t *data = malloc(sizeof(data_t));
    if  (data == NULL) {
        fprintf(stderr, "ERROR: Chyba alokácie!\n");
        exit(1);
    }
    data->count = 0;
    data->count_lines = 0;
    data->strings_array = NULL;
    return data;
}

//funkcia na vymazanie štruktúry
void dtor(data_t *data) {
    free(data->strings_array);
    free(data);
}

//funckia na získanie dát zo vstupu/vstupného súboru
void write_data(data_t *data, int c) {
    data->count = data->count + 1;
    //alokácia pre prvé písmeno
    if (data->strings_array == NULL) {
        data->strings_array = malloc(sizeof(char));
        if (data->strings_array == NULL) {
            fprintf(stderr, "ERROR: Chyba alokácie!\n");
            dtor(data);
            exit(1);
        }
    //alokácia pre následujúce písmeno
    } else {
        data->strings_array = realloc(data->strings_array, sizeof(char)*data->count);
        if (data->strings_array == NULL) {
            fprintf(stderr, "ERROR: Chyba alokacie!\n");
            dtor(data);
            exit(1);
        }
    }
    //uloženie písmena
    data->strings_array[data->count-1] = c;
    //počítadlo riadkov
    if (c == '\n') {
        data->count_lines = data->count_lines + 1;
    }
}

//funkcia na prečítanie súboru zadaného uživateľom
void read_file(char *fileName, data_t *data) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Neplatný názov súboru!\n");
        dtor(data);
        exit(1);
    }
    //postupné získavanie písmen zo súboru
    int c = fgetc(file);
    while (c != EOF) {
        write_data(data, c);
        c = fgetc(file);
    }
    fclose(file);
}

//funckia na prečítanie vstupu zo stdin
void read_stdin(data_t *data) {
    //postupné získavanie písmen zo stdin
    int c = getchar();
    while (c != EOF) {
        write_data(data, c);
        c = getchar();
    }
}

//funkcia na získanie parametru a overenie jeho správnosti
int get_parameter(char nameOfParam[], char param[]) {
    if (strcmp(nameOfParam, "-n") == 0) {
        if (atoll(param) >= 0) {
            return 1;
        } else {
            fprintf(stderr, "ERROR: Číslo parametru musí byť väčšie alebo rovné 0!\n");
            return -1;
        }
    } else {
        fprintf(stderr, "ERROR: Zadané zlé meno paramteru!\n");
        return -1;
    }
    return 0;
}

//funckia na vypísanie posledných n riadkov
void print_lines(data_t *data, long long param) {
    if ((data->count_lines - param) <= 0 && data->strings_array != NULL) {
        printf("%s", data->strings_array);
    } else {
        int count_l = 0;
        int index = 0;
        for (int i = strlen(data->strings_array); i > 0; i--) {
            //získanie správneho indexu od ktorého chceme vypísať dáta
            if (data->strings_array[i-1] == '\n') {
                count_l++;
            }
            if (count_l == param+1) {
                index = i;
                break;
            }
        }
        //výpis
        for (unsigned long i = index; i < strlen(data->strings_array); i++) {
            printf("%c", data->strings_array[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    data_t *data = ctor();
    //ak uživateľ nezmení parameter -n tak sa štandartne vypíše poslendých 10 riadkov
    long long param = 10;

    if (argc > 2) {
        int p = get_parameter(argv[1], argv[2]);
        if (p == 1) {
            param = atoll(argv[2]);
        } else if (p == -1) {
            dtor(data);
            exit(1);
        }
        if (argc > 3) {
            read_file(argv[3], data);
        }
        else {
            read_stdin(data);
        }
    } else {
        if (argc > 1) {
            read_file(argv[1], data);
        } else {
            read_stdin(data);
        }
    }

    print_lines(data, param);
    dtor(data);
}
