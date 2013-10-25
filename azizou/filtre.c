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

int main(int argc, const char * argv[])
{
    FILE * fichier = NULL;
	int n = 0;
	//int m = 0;
	int *vecteur=NULL;
	//int *ptrTab=NULL;
	
    //Check le nombre de paramètre et dispatche les vérifications
    nombreParametre(argc, argv);
    
    
    
    
    
    
	
	
    
    
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
		errOuverture();
	}
    
	
	fclose(fichier);
    
    return 0;
}

