/*
 * File:   testFonction.c
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 2013-10-20, 01:10:21
 */

#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

/*
 * Simple C Test Suite
 */

void testTaille_max_lignes() {
    int* vecteur;
    int v;
    int result = taille_max_lignes(vecteur, v);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testTaille_max_lignes (testFonction) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% testFonction\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testTaille_max_lignes (testFonction)\n");
    testTaille_max_lignes();
    printf("%%TEST_FINISHED%% time=0 testTaille_max_lignes (testFonction)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
