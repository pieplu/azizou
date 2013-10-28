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





int *creerVecteur(FILE* fichier, int n)
{
    int ligne = 0;
    int nbChar = 0;
    int curNb=0;
    int nxtNb = 0;
    
    int * nbCharLigne;
    
    nbCharLigne = malloc( n * sizeof(int));
    
 
    
    while (!feof(fichier))
    {
        curNb=0;
        curNb=fgetc(fichier)-'0';
        if (curNb=='\n')
        {
            
            *nbCharLigne=nbChar;
            nbCharLigne++;
        }
        else if (curNb==' ')
        {
            break;
        }
        else
        {
        while ((nxtNb=fgetc(fichier))!= ' ' && nxtNb!='\n')
        {
            if (nxtNb=='-')
            {
                nxtNb=(fgetc(fichier)-'0')*(-1);
            }
            
            nxtNb-='0';
            curNb=(curNb*10)+nxtNb;
            nxtNb=0;
        }
        if (nxtNb=='\n' || nxtNb==-1)
        {
            
            nbChar++;
            *nbCharLigne=nbChar;
            nbCharLigne++;
            nbChar=-1;
            
            break;
        }
        nbChar++;
        }
    }
    
    
    
    for (int i = 0; i < n; i++)
    {   nbCharLigne--;
        printf("%d", *nbCharLigne);
        nbCharLigne++;

    }
    
    
    rewind(fichier);
    return nbCharLigne;
}







int main(int argc, const char * argv[])
{
    FILE * fichier = NULL;
	int *vecteur=NULL;
	
    
    nombreParametre(argc, argv);
    
    
    int tab[4] = {2,2,0,5};
   

    //seek_option(argv, 'C');
    
	fichier = fopen("test01.txt", "r");
	if(fichier != NULL)
	{
        //vecteur = creerVecteur(fichier, n);
        
        int n =nbre_lignes_fichier(fichier);
        int m = taille_max_lignes(tab, 4);
        

        vecteur = charger(fichier, tab, n, m);
        
        

	}
	else
	{
		errOuverture();
	}
    
	
	fclose(fichier);
    
    return 0;
}

