//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"

void errInconnue(){
    signaler_erreur(OPTION_INCONNUE_ERREUR);
    exit(1);
}
void errOuverture(void){
    signaler_erreur(OUVERTURE_FICHIER_ERREUR);
    exit(1);
}


int checkOpt1(const char **argv){
    return strcmp(&argv[2][1], "C") || strcmp(&argv[2][1], "L")    ;
}

int checkOpt2(const char **argv){
    return strcmp(&argv[4][1], "L") || strcmp(&argv[4][1], "C");
}

int checkTiretLettre(const char** argv, int position){
    return strcmp(&argv[position][0], "-");
}

void cas3(const char** argv){
    if (checkOpt1(argv) || checkTiretLettre(argv,2)){
        errInconnue();
    }
}

void cas5(const char** argv)
{
    if (checkOpt1(argv) || checkOpt2(argv) || checkTiretLettre(argv,2) || checkTiretLettre(argv,4)){
        errInconnue();
    }
}

void nombreParametre(int argc, const char *argv[]){
    // nombre params
    switch (argc){
        case 1: //FONCTION errInconnue() à mettre
            break;
        case 2:
            break;
        case 3: cas3(argv);
            break;
        case 4:
            break;
        case 5: cas5(argv);
            break;
        case 6:
            break;
        default: errInconnue();
            break;
    }
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
            //printf("%d à %p\n", *nbCharLigne, nbCharLigne);
            nbCharLigne++;
            nbNombres=0;
		}
        
		unNbLue=false;
        
	}while(temp != EOF);
    
    rewind(fichier);
    
    return vecteur;
}







int main(int argc, const char * argv[])
{
    FILE * fichier = NULL;
	int *vecteur=NULL;
	int * ptrTableau2d=NULL;
    
    //nombreParametre(argc, argv);
    
    
    //int tab[4] = {2,2,0,5};
   

    //seek_option(argv, 'C');
    
	fichier = fopen("test01.txt", "r");
	if(fichier != NULL)
	{
        
        
        int n =nbre_lignes_fichier(fichier);
        vecteur = creerVecteur(fichier, n);
        int m = taille_max_lignes(vecteur, 4);
        ptrTableau2d = charger(fichier, vecteur, n, m);
        affiche_Tab2D(ptrTableau2d, n, m);
        
        

	}
	else
	{
		errOuverture();
	}
    
	
	fclose(fichier);
    
    return 0;
}

