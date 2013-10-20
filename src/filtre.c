//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"


int main(int argc, const char * argv[])
{
    

<<<<<<< HEAD:src/filtre.c
    FILE *fichier = NULL;
=======
    FILE * fichier = NULL;
	int n = 0;
	int m = 0;
	
	int *vecteur=NULL;
	int *ptrTab=NULL;
	
	
	
>>>>>>> 4e449ec1f5633e356d21b44d25f935bdbe2e65ba:azizou/filtre.c

	fichier = fopen("test01.txt", "r");

	
	if(fichier != NULL)
	{
<<<<<<< HEAD:src/filtre.c
		printf("%d", nbre_lignes_fichier(fichier));
		
=======
		n = nbre_lignes_fichier(fichier);
		vecteur = malloc(n*sizeof(int));	
>>>>>>> 4e449ec1f5633e356d21b44d25f935bdbe2e65ba:azizou/filtre.c
	}
	else 
	{
		printf("Echec de l'ouverture");
	}

	
	fclose(fichier);
 
    return 0;
}

