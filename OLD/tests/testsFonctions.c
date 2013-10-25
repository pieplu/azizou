#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"


//Tabeleaux pour tests
int tab1[]={2,5,2,3,9,22,0,7};
int tab2[4]={NULL,NULL};



// -------------  Nb lignes
// 
void testNbre_lignes_fichier() {
    FILE * fichier = NULL;
   fichier = fopen("test01.txt", "r");
   int result = nbre_lignes_fichier(fichier);
    if (result != 6) {
        printf("%%TEST_FAILED%% time=0 testname=testNbre_lignes_fichier (tailleMaxLignes) message=error message sample\n");
    }
   fclose(fichier);
}
//test Vide
void testNbre_lignes_fichierVide() {
    FILE * fichier = NULL;
   fichier = fopen("testVide.txt", "r");
   int result = nbre_lignes_fichier(fichier);
    if (result != 1) {
        printf("%%TEST_FAILED%% time=0 testname=testNbre_lignes_fichier (tailleMaxLignes) message=error message sample\n");
    }
   fclose(fichier);
}

// -------------  Max Ligne
//
void testTaille_max_lignes() {
    int* vecteur = tab1;
    int v =8;
    int result = taille_max_lignes(vecteur, v);
    if (result != 22) {
        printf("%%TEST_FAILED%% time=0 testname=testTaille_max_lignes (testsFonctions) message=error message sample\n");
    }
}
//test si valeur == NULL
void testTaille_max_lignes2() {
    int* vecteur = tab2;
    int v =4;
    int result = taille_max_lignes(vecteur, v);
    if (result != 0) { 
        printf("%%TEST_FAILED%% time=0 testname=testTaille_max_lignes (testsFonctions) message=error message sample\n");
    }
}


// ------------------------------------------------------------------------------------------------------------
// -----------------------------------------------        MAIN            -------------------------------------
// ------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% testsFonctions\n");
    printf("%%SUITE_STARTED%%\n");

    //maxlignes
    printf("%%TEST_STARTED%%  testTaille_max_lignes (testsFonctions)\n");
    testTaille_max_lignes();
    printf("%%TEST_FINISHED%% time=0 testTaille_max_lignes (testsFonctions)\n");
    printf("%%TEST_STARTED%%  testTaille_max_lignes2 (testsFonctions)\n");
    testTaille_max_lignes2();
    printf("%%TEST_FINISHED%% time=0 testTaille_max_lignes2 (testsFonctions)\n");

    //nbLignes
    printf("%%TEST_STARTED%%  testNbre_lignes_fichier (tailleMaxLignes)\n");
    testNbre_lignes_fichier();
    printf("%%TEST_FINISHED%% time=0 testNbre_lignes_fichier (tailleMaxLignes)\n");
    printf("%%TEST_STARTED%%  testNbre_lignes_fichierVide (tailleMaxLignes)\n");
    testNbre_lignes_fichierVide();
    printf("%%TEST_FINISHED%% time=0 testNbre_lignes_fichierVide (tailleMaxLignes)\n");
    
    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
