//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"


int main(int argc, const char * argv[])
{

    FILE * fichier = NULL;
	char c;
	fichier = fopen("../../azizou/test01.txt", "r");

	
	if(fichier != NULL)
	{
		
		printf("%d", nbre_lignes_fichier(fichier));
		
	}
	else 
	{
		printf("Echec de l'ouverture");
	}

	
	
	fclose(fichier);
 
    return 0;
}

