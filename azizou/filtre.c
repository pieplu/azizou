//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"


int checkOpt1(const char **argv){
    return strcmp(&argv[2][1], "C") || strcmp(&argv[2][1], "L")    ;
}

int checkOpt2(const char **argv){
    return strcmp(&argv[4][1], "L") || strcmp(&argv[4][1], "C");
}

int checkTiretLettre(const char** argv, int position){
    return strcmp(&argv[position][0], "-");
}



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
    
    //nombreParametre(argc, argv);
   

    
    
//	fichier = fopen("test01.txt", "r");
    fichier = fopen(argv[1], "r");
	if(fichier != NULL)
	{
        
        
        int n =nbre_lignes_fichier(fichier);
        vecteur = creerVecteur(fichier, n);
        int m = taille_max_lignes(vecteur, 4);
        ptrTableau2d = charger(fichier, vecteur, n, m);
        n = tailleApresSupp(vecteur, n);
        //affiche_Tab2D(ptrTableau2d , n , m);
        
       printf("\n%d\n", get_nbre_domaines(argv, 4));
        printf("%d",seek_option(argv, 'L'));
        

	}
	else
	{
		
	}
    
	free(vecteur);
    free(ptrTableau2d);
	fclose(fichier);
    
    return 0;
}

