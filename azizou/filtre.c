//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"


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



int tailleApresSupp(int *vecteur, int taille_vecteur)
{
    int ligne0=0;
    for (int i = 0; i < taille_vecteur; i++) {
        if (vecteur[i]==0) {
            ligne0++;
        }
    }
    return taille_vecteur-ligne0;
}



int main(int argc, char * const argv[])
{
    
    
    
    FILE * fichier = NULL;
	int *vecteur=NULL;
	int * ptrTableau2d=NULL;
    int * ptrTabApresFiltre = NULL;
    int *ControlL = NULL;
    int *ControlC = NULL;
    fichier = fopen(argv[1], "r");
	if(fichier != NULL)
	{
        
        
        int n =nbre_lignes_fichier(fichier);
        vecteur = creerVecteur(fichier, n);
        int m = taille_max_lignes(vecteur, n);
        ptrTableau2d = charger(fichier, vecteur, n, m);
        
        
        n = tailleApresSupp(ptrTableau2d, n);
        //affiche_Tab2D(ptrTableau2d , n , m);
        
        ControlL = control(argv, n, 'L', ptrTableau2d);
        ControlC = control(argv, m, 'C', ptrTableau2d);
        affiche_Tab2D(ptrTableau2d , n , m);
        
        ptrTabApresFiltre = filter(ptrTableau2d, &n, &m, ControlC, ControlL);
        affiche_Tab2D(ptrTabApresFiltre, n, m);
        
  
        

	}
	else
	{
		signaler_erreur(OUVERTURE_FICHIER_ERREUR);
	}
    
	free(vecteur);
    free(ptrTableau2d);
    free(ptrTabApresFiltre);
    free(ControlC);
    free(ControlL);
	fclose(fichier);
    
    return 0;
}

