/*
 * File:   testFonctions.c
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 2013-10-19, 23:52:02
 */

#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}
/*
void testCheck_domaine() {
    char* domaine;
    int result = check_domaine(domaine);
    if (1 ) {
        CU_ASSERT(0);
    }
}*/

/*
void testNbre_lignes_fichier() {
    FILE* fp;
    int result = nbre_lignes_fichier(fp);
    if (1) {
        CU_ASSERT(0);
    }
}*/

void testTaille_max_lignes() {
    int vecteur[5] = {3,4,5,6,8};
    int v=5;
    int result = taille_max_lignes(vecteur, v);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

