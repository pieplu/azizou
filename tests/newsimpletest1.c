/*
 * File:   newsimpletest1.c
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 2013-10-20, 01:17:46
 */

#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

/*
 * Simple C Test Suite
 */

int tab1[]={2,5,2,3,9,22,0,7};

void testTaille_max_lignes() {
    int* vecteur = tab1; //surement mauvais, le test faill tt le temps, à voir
    int v =8;
    int result = taille_max_lignes(vecteur, v);
    if (result != 0) {
        printf("%%TEST_FAILED%% time=0 testname=testTaille_max_lignes (newsimpletest1) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% newsimpletest1\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testTaille_max_lignes (newsimpletest1)\n");
    testTaille_max_lignes();
    printf("%%TEST_FINISHED%% time=0 testTaille_max_lignes (newsimpletest1)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
