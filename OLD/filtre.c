//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"


int main(int argc, const char * argv[])
{
    

    FILE * fichier = NULL;
	int n = 0;
	//int m = 0;
        int nbChar = 0;
        char c;
	
	int *vecteur=NULL;
	//int *ptrTab=NULL;
	
	
	


	fichier = fopen("test01.txt", "r");

	
	if(fichier != NULL)
	{

		printf("%d", nbre_lignes_fichier(fichier));
                int tab[4]={3,4,5,2};
		printf("taille 4 rempli :%d", taille_max_lignes(tab, 4));


		n = nbre_lignes_fichier(fichier);
		vecteur = malloc( n * sizeof(int));

                



	}
	else 
	{
		signaler_erreur(OUVERTURE_FICHIER_ERREUR);
	}

	
	fclose(fichier);
 
    return 0;
}
