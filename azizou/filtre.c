//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

/*
 Le programme filtre sert à filtrer et afficher une matrice de chaines de caractères.
 Elle provient d'un fichier ou plusieurs fichiers (fusioner horizontalement ou verticalement.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"
#include "affichage.h"


/*
 * Crée un vecteur contenant le nombre d'éléments d'un fichier (séparé par des blanc)
 * et set le nombre de ligne non vide de ce fichier
 *@param fichier  : le fichier à parcourir
 *@param nbLigne  : le nombre de ligne non vide
 *@return le vecteur
 */
int *creerVecteur(FILE* fichier, int * nbLigne)
{
    rewind(fichier);
    int * nbCharLigne;
    int nombreLigneVecteur = 0;
    nbCharLigne = malloc( (*nbLigne) * sizeof(int));
    int *vecteur = nbCharLigne;
    
    int temp;
    int nbNombres=0;
    int unNbLue =false;
    
    do{
        temp=fgetc(fichier);
        while(temp != ' ' && temp != '\n' && temp != EOF){
            temp=fgetc(fichier);
            unNbLue=true;
        }
        
        if(unNbLue){ ++nbNombres; }
        
        if(temp == '\n' || temp == EOF){
            if(nbNombres != 0){
                *nbCharLigne = nbNombres;
                nbCharLigne++;
                nombreLigneVecteur++;
                nbNombres=0;
            }
        }
        unNbLue=false;
        
    }while(temp != EOF);
    
    rewind(fichier);
    *nbLigne = nombreLigneVecteur;
    return realloc(vecteur , nombreLigneVecteur*sizeof(int));
}




/*
 * Vérifie qu'une option n'est pas en double
 * Déclanche une erreur si c'est le cas
 *@param argv   : tableau pointant les paramères du programme
 *@param option : l'option à vérifier
 */
void checkOptionEnDouble(char* const *argv, char option) {
    int pos = seek_option(argv, option);
    if (pos != -1) {
        int enDouble = seek_option(&argv[pos +1 ], option);
        if (enDouble != -1) {
            signaler_erreur(OPTION_ERREUR);
            exit(1);
        }
    }
}

/*
 * Vérifie les options passées en paramétre du programme,
 * Déclanche une erreur si la syntaxe est mauvaise
 *@param argv   : tableau pointant les paramères du programme
 */
void verificationOptions(char * const argv[]){
    int Vpos = seek_option(argv, 'V');
    int Hpos = seek_option(argv, 'H');
    if (Hpos != 1 && Vpos != 1) {
        signaler_erreur(OPTION_ERREUR);
        exit(1);
    }
    checkOptionEnDouble(argv, 'C');
    checkOptionEnDouble(argv, 'L');
}


/*
 * Main du programme filtre
 *@param argv  : tableau pointant les paramères du programme
 *@param argc  : nombre de paramètres du programme
 */
int main(int argc, char * const argv[])
{
    
    FILE * fichier = NULL;
    int *vecteur=NULL;
    int *ControlL = NULL;
    int *ControlC = NULL;
    int n = 0;
    int m = 0;
    
    verificationOptions(argv);
    
    int nbFichiers = get_nbre_domaines(argv, 1);
    
    stab2d *tableauStructures = malloc(nbFichiers*sizeof(stab2d));
    stab2d unTableau;
    for (int i=0; i<nbFichiers; i++) {
        fichier = fopen(argv[(i+2)], "r");
        if(fichier == NULL) {
            signaler_erreur(OUVERTURE_FICHIER_ERREUR);
            exit(1);
        }
        
        n = nbre_lignes_fichier(fichier);
        vecteur = creerVecteur(fichier, &n);
        m = taille_max_lignes(vecteur, n);
        if(!m)  {
            signaler_erreur(FICHIER_SANS_DONNEE_ERREUR);
            exit(1);
        }

        unTableau.ptr = charger(fichier, vecteur, n, m);
        unTableau.lignes = n;
        unTableau.colonnes = m;
        
        tableauStructures[i] = unTableau; // fait une copie
        fclose(fichier);

    }
    

    stab2d tabFusion = fusionMatrices(tableauStructures, nbFichiers, argv[1][1]);
    n = tabFusion.lignes;
    m = tabFusion.colonnes;
    ControlL = control(argv, n, 'L');
    ControlC = control(argv, m, 'C');
    
    tabFusion.ptr = filter(tabFusion.ptr, &tabFusion.lignes, &tabFusion.colonnes, ControlC, ControlL);
    
    affiche_Tab2D(tabFusion);
    
    

    free(vecteur);
    free(tableauStructures);
    free(ControlC);
    free(ControlL);
       
    return 0;
}

