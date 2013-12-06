//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

/*
 Le programme filtre sert à filtrer et afficher une matrice contenue dans un fichier
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"
#include "affichage.h"


// retourne un tableau contenant le nombre de caractères de chaques lignes du fichier
int *creerVecteur(FILE* fichier, int nbLigne)
{
    rewind(fichier);
    int * nbCharLigne;
    
    nbCharLigne = malloc( nbLigne * sizeof(int));
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
        
		if(unNbLue){
			++nbNombres;
		}
		
		if(temp == '\n' || temp == EOF){
            *nbCharLigne = nbNombres;
            nbCharLigne++;
            nbNombres=0;
		}
        
		unNbLue=false;
        
	}while(temp != EOF);
    
    rewind(fichier);
    return vecteur;
}


// retourne la nouvelle taille du vecteur en ignaorant les lignes vides
int tailleApresSupp(int *vecteur, int taille_vecteur)
{
    int ligne0=0;
    for (int i = 0; i < taille_vecteur; i++) {
        if (vecteur[i]==0) {
            ligne0++;
        }
    }
    return taille_vecteur - ligne0;
}



int main(int argc, char * const argv[])
{
    
    FILE * fichier = NULL;
	int *vecteur=NULL;
	char ** ptrTableau2d = NULL;
    char ** ptrTabApresFiltre = NULL;
    int *ControlL = NULL;
    int *ControlC = NULL;
    
    int Cpos = seek_option(argv, 'C');
    int Lpos = seek_option(argv, 'L');
    if (Cpos ==-1 && Lpos == -1 && argc > 2) {
        signaler_erreur(OPTION_ERREUR);
        exit(1);
    }

    int doubleC = seek_option(&argv[Cpos +1 ], 'C');
    int doubleL = seek_option(&argv[Lpos +1 ], 'L');
    if (doubleC != -1 || doubleL != -1) {
        signaler_erreur(OPTION_ERREUR);
        exit(1);
    }
    
    fichier = fopen(argv[1], "r");
	if(fichier == NULL)	{
        signaler_erreur(OUVERTURE_FICHIER_ERREUR);
        exit(1);
    }
    
    int n =nbre_lignes_fichier(fichier);
    vecteur = creerVecteur(fichier, n);
    int m = taille_max_lignes(vecteur, n);
    if(!m)	{
        signaler_erreur(FICHIER_SANS_DONNEE_ERREUR);
        exit(1);
    }
    
    stab2d* tableau = (stab2d*)malloc(sizeof(stab2d));
    
    tableau->ptr = charger(fichier, vecteur, n, m);
    n = tailleApresSupp(vecteur, n);
    tableau->lignes = n;
    tableau->colonnes = m;
    
    ControlL = control(argv, n, 'L');
    ControlC = control(argv, m, 'C');
    
  //  ptrTabApresFiltre = filter(ptrTableau2d, &n, &m, ControlC, ControlL);
    
    
   // tableau->ptr = ptrTabApresFiltre;
    affiche_Tab2D(*tableau);
    
	
	free(vecteur);
    free(tableau);
    free(ptrTableau2d);
    free(ptrTabApresFiltre);
    free(ControlC);
    free(ControlL);
	fclose(fichier);
    
    return 0;
}

