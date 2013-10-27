//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#include <stdio.h>
#include "fonctions.h"
#include <stdlib.h>


//affiche un message d'erreur sur le canal d'erreur selon les cas définis
void
signaler_erreur(int err)
{
    switch (err)
    {
        case OUVERTURE_FICHIER_ERREUR :
            fprintf(stderr,"Erreur d'ouverture du fichier.\n");
            break;
        case SYNTAX_DOMAIN_ERREUR :
            fprintf(stderr,"Erreur de syntaxe dans un domaine.\n");
            break;
        case OPTION_INCONNUE_ERREUR :
            fprintf(stderr,"Option inconnue.\n");
            fprintf(stderr,"Usasge : filtre <fichier> [-C <liste>] [-L <liste>]\n");
            fprintf(stderr,"         filtre <fichier> [-L <liste>] [-C <liste>]\n");
            break;
        case OPTION_DUPLIQUEE_ERREUR :
            fprintf(stderr,"Option en double.\n");
            break;
        case FICHIER_SANS_ENTIER_ERREUR :
            fprintf(stderr,"Le fichier ne comporte aucun entier.\n");
            break;
        case TABLEAU2D_VIDE_ERREUR :
            fprintf(stderr,"Tableau vide!\n");
            break;
        default :
            fprintf(stderr,"Erreur inconnue.\n");
            break;
    }
    
}



//affiche un tableau 2D nxm
void
affiche_Tab2D(int *ptr, int n, int m)
{
    if (n>0 && m>0 && ptr!=NULL)
    {
        int (*lignePtr)[m];
		
        
        lignePtr = (int (*)[m]) ptr;
        
        for (int i = 0 ; i < n ; i++)
        {
            for (int j = 0 ; j < m ; j++)
            {
                printf("%5d ",lignePtr[i][j]);
            }
            printf("\b\n");
        }
    }
    else
    {
        signaler_erreur(TABLEAU2D_VIDE_ERREUR);
    }
}




// retourne le nombre de lignes total du fichier pointé par fp
int nbre_lignes_fichier(FILE *fp)
{
	int nbLigne=1;
	char c = 0;
	if(fp != NULL)
	{
		while (c != EOF)
		{
			c = fgetc(fp);
			if (c == '\n')
			{
				nbLigne++;
			}
		}
		
	}
    rewind(fp);
	return nbLigne;
	
}


int taille_max_lignes(int * vecteur , int v){
    int maxVal=0;
    for(int i=0; i < v; i++){
        maxVal = *(vecteur + i)>maxVal ? *(vecteur + i) : maxVal;
    }
    return maxVal; // 0 pour le test
}



//vecteur[i] représente le nombre d'entiers à ligne i du fichier pointé par fp.
//si vecteur[i]==0, la ligne i du fichier est ignorée car elle est vide d'entier.
//Cette fonction retourne un pointeur sur la première case d'un tableau 2D n x m
//Le tableau 2D de taille n x max_veteur est rempli à partir du fichier.
//Chaque ligne du fichier qui contient au moins un entier donne lieu à une ligne dans le tableau 2D.
int *charger(FILE *fp, int * vecteur, int taille_vecteur, int max_vecteur)
{
    int tailleFichier=taille_vecteur;
    int **tableau2D=NULL;
    int nbCurrent = 0;
    int nbDeNombre = 0;
    
    for (int i = 0; i < taille_vecteur; i++)
    {
        if (vecteur[i]==0)
        {
            taille_vecteur--;
        }
    }

    tableau2D = malloc(taille_vecteur* sizeof(int*));
    for (int i = 0; i < taille_vecteur; i++){
        tableau2D[i] = malloc(max_vecteur * sizeof(int));
    }
    
//    while (!feof(fp))
//    {
//        fscanf(fp, "%d", &nbCurrent);
//        if (nbCurrent=='\n')
//        {
//            nbDeNombre=0;
//        }
//    }
    


    
    
    
    return 0;
}




//verifie si un domaine est syntaxiquement correcte
// retourne 1 si correcte et 0 sinon
int check_domaine(char *domaine) ;

//argv représente le tableau des paramères du programme
//cette fonction retourne la taille de la liste de domaine à partir argv[pos]
//la fin la liste est localisée soit par la fin du tableau d'argument soit par une option connue
//pos devrait représenter l'indice de l'option dans argv et retourner la taille de la liste
int get_nbre_domaines(char  *const argv[], int pos);

//retourne 1 si la syntaxe  de domaine est correcte et place le début et la fin du domaine dans debut et fin
//retourne 0 si la syntaxe  de domaine est incorrecte
//max est utilisé pour que <nun>- represente le domaine <num>-max
int get_debut_fin_domaine(char * domaine, int max, int *debut, int *fin);

//argv représente le tableau pointant les paramères du programme
//retourne l'indexe de option dans argv. par exemple esi option est 'C'
// la valeur retournée est l'indexe de la chaine "-C" dans argv
// retourne -1 si l'option n'est pas trouvée dans argv
int seek_option(char *const argv[], char option)
{
    
    return 0;
}


int checkArg(const char **argv){
    
    printf("%s", *argv);
    
    return 0;
}

//c est soit 'C', soit 'L'.
//dim est censée représenter soit le nombre de lignes dans le tableau 2D soit le nombre de colonnnes.
//argv représente le tableau pointant les paramères du programme.
//retourne un tableau d'entiers de taille dim rempli avec des 0 et des 1 :
//une case est remplie avec 0 si elle correspond à une ligne ou une colonne qui ne va pas
//être supprimée selon argv et l'option c ;
//une case est remplie avec 1 si elle correspond à une ligne ou une colonne qui va
//être supprimée selon argv et l'option c
int * control(char *const argv[], int dim, char c);

//mat pointe le début d'un tableau 2D de taill *n x *m.
//controlC de taille *m est un vecteur indiquant les colonnes à supprimer selon la fonction control.
//controlV de taille *n est un vecteur indiquant les lignes à supprimer selon la fonction control.
//retourne un pointeur sur le début d'un tableau 2D de la bonne taille après application
// des suppressions données par controlC et controlL  et place la nouvelle taille du tableau dans *n et *m.
//retourne NULL sil le tableau résultant est vide.
int *filter(int * mat, int *n, int *m, int *controlC, int *controlL);










