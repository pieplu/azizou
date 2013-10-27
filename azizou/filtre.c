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


int *nbCharParLigne(FILE* fichier)
{
    int ligne = 0;
    int nbChar = 0;
    int nombre=0;
    int* nbCharLigne;
    char **tabTemp=NULL;
    int n =nbre_lignes_fichier(fichier);
    
    nbCharLigne = malloc( n * sizeof(int));
    tabTemp=malloc( n * sizeof(int));
                   
    for (int i = 0; i < n; i++){
        tabTemp[i] = malloc(40 * sizeof(char));
        fgets(tabTemp[i], 40, fichier);
    }
    
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j<40; j++)
        {
            sscanf(tabTemp[i], "%d", &nombre);
            if (nombre='\n')
            {
                break;
            }
            nbChar++;
        }
        
        nbCharLigne[i]=nbChar;
        printf("%d",nbCharLigne[i]);
        nbChar=0;
    }
    
    
//    while(!feof(fichier))
//    {
//        
//        
//        fscanf(fichier,"%d", &nombre);
//        printf("%d",nombre);
//        nbChar++;
//        if(nombre=='\n')
//        {
//            nbCharLigne[ligne] = nbChar;
//            nbChar = 0;
//            ligne++;
//            printf("\n");
//        }
//        
//    }
    
    return nbCharLigne;
}







int main(int argc, const char * argv[])
{
    FILE * fichier = NULL;
	int n = 0;
	int *vecteur=NULL;
	
    
    nombreParametre(argc, argv);
    
    
    int tab[4] = {1,0,6,3};
   

    //seek_option(argv, 'C');
    
	fichier = fopen("test01.txt", "r");
	if(fichier != NULL)
	{
        vecteur = nbCharParLigne(fichier);
		
        charger(fichier, tab, 4, 6);
        
        

	}
	else
	{
		errOuverture();
	}
    
	
	fclose(fichier);
    
    return 0;
}

