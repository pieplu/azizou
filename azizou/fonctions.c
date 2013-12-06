//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "affichage.h"




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


// retourne le max du tableau pointé par vecteur et de taille v
// retourne 0 si le tableau est vide (NULL)
int taille_max_lignes(int * vecteur , int v){
    int maxVal=0;
    for(int i=0; i < v; i++){
        maxVal = *(vecteur + i)>maxVal ? *(vecteur + i) : maxVal;
    }
    return maxVal;
}


// retourne une valeur taille auquelle l'on a soustrai le nombre de case
// contenant 0 du tableau vercteur
int tailleMoinsCasesZero(int *vecteur, int taille_vecteur)
{
    int ligne0=0;
    for (int i = 0; i < taille_vecteur; i++) {
        if (vecteur[i]==0) {
            ligne0++;
        }
    }
    return taille_vecteur - ligne0;
}

// retourne le nombre de case contenant 0 dans le vecteur
int NbCaseZero(int *vecteur, int taille_vecteur)
{
    int ligne0=0;
    for (int i = 0; i < taille_vecteur; i++) {
        if (vecteur[i]==0) {
            ligne0++;
        }
    }
    return ligne0;
}


//vecteur[i] représente le nombre d'entiers à ligne i du fichier pointé par fp.
//si vecteur[i]==0, la ligne i du fichier est ignorée car elle est vide d'entier.
//Cette fonction retourne un pointeur sur la première case d'un tableau 2D n x m
//Le tableau 2D de taille n x max_veteur est rempli à partir du fichier.
//Chaque ligne du fichier qui contient au moins un entier donne lieu à une ligne dans le tableau 2D.
char **charger(FILE *fp, int * vecteur, int taille_vecteur, int max_vecteur)
{
    char curElem[100];
    char *vide = "";

    int nvlleTaille = tailleMoinsCasesZero(vecteur, taille_vecteur);
    char *(*tableau2dim)[max_vecteur];

    tableau2dim=malloc(max_vecteur*nvlleTaille*sizeof(char *));
    for(int i = 0; i<nvlleTaille; i++){
        for (int j = 0; j<max_vecteur; j++) {
            tableau2dim[i][j] = vide;
        }
    }
    
    while (!feof (fp)){
        int nbLigne = 0;
        // passe de ligne en ligne
        for (int y = 0; nbLigne < taille_vecteur; y++, nbLigne++){
            //ignore les lignes vide
            while (*vecteur == 0){
                vecteur++;
                nbLigne++;
            }
            // prend toutes les valeures de la ligne
            for (int x = 0; x < max_vecteur; x++){
                if(x < *vecteur){
                    fscanf (fp, "%s", curElem);
                    tableau2dim[y][x] = strcpy(malloc(sizeof(curElem)),curElem);
                    //printf("%d ",&tableau2dim[y][x]);
                }
            }
            vecteur++;
        }
    }
    
    rewind(fp);
    return &(tableau2dim[0][0]);
    //si temps:
    //recuperation de la chaine a refaire (fgets)
}


//verifie si un domaine est syntaxiquement correcte
// retourne 1 si correcte et 0 sinon
int check_domaine(char *domaine){
    
    int nbTiret=0;
    int nbNombre=0;
    
    for (unsigned long taille = strlen(domaine); taille>0; taille--){
        if (*domaine == '-') {
            nbTiret++;
        }else if(*domaine >= '0' && *domaine <= '9'){
            nbNombre++;
        }else{
            return 0;
        }
        domaine++;
    }
    
    // retourne vrai s'il y a un tiret ou moins et un nombre ou plus.
    return (nbTiret <= 1 && nbNombre > 0);
}


//argv représente le tableau des paramères du programme
//cette fonction retourne la taille de la liste de domaine à partir argv[pos]
//la fin la liste est localisée soit par la fin du tableau d'argument soit par une option connue
//pos devrait représenter l'indice de l'option dans argv et retourner la taille de la liste
int get_nbre_domaines(char  *const argv[], int pos)
{
    int compt = 0;
    
    while (argv[pos+1] != '\0')
    {
        if (!(strcmp(argv[pos+1], "-C")) || !(strcmp(argv[pos+1], "-L")) ) {
           return compt;
        }
        else{
            compt++;
            pos++;
        }
    }
    return compt;
}


//retourne 1 si la syntaxe  de domaine est correcte et place le début et la fin du domaine dans debut et fin
//retourne 0 si la syntaxe  de domaine est incorrecte
//max est utilisé pour que <nun>- represente le domaine <num>-max
int get_debut_fin_domaine(char * domaine, int max, int *debut, int *fin)
{
    unsigned long tailleDomaine = strlen(domaine);
    char * tokens=NULL;
    int curChar=0;
    
    if (!check_domaine(domaine))
    {
        return 0;
    }
    
    // -<num>
    if (domaine[0]=='-')
    {
        tokens = strtok(domaine, "-");
        
        while (*tokens!='\0')
        {
            curChar = curChar*10+(*tokens-'0');
            tokens++;
            
        }
        *debut = 0;
        *fin = curChar;
        
    }
    // <num>-
    else if (domaine[tailleDomaine-1]=='-')
    {
        tokens = strtok(domaine, "-");
        
        while (*tokens!='\0')
        {
            curChar = curChar*10+(*tokens-'0');
            tokens++;
            
        }
        *debut = curChar;
        *fin = max;
    }
    
    else if(domaine[0] != '-' && domaine[tailleDomaine] != '-')
    {
        // <num>
        if (strchr(domaine, '-') == NULL)
        {
            while (*domaine!='\0')
            {
                curChar = curChar*10+(*domaine-'0');
                domaine++;
                
            }
            *debut = curChar;
            *fin = curChar;
        }
        // <num>-<num>
        else
        {
            tokens = strtok(domaine, "-");
            
            while (*tokens!='\0')
            {
                curChar = curChar*10+(*tokens-'0');
                tokens++;
                
            }
            *debut = curChar;
            curChar=0;
            tokens = strtok(NULL,"-");
            while (*tokens!='\0')
            {

                curChar = curChar*10+(*tokens-'0');
                tokens++;
                
            }
            *fin = curChar;
        }
    }
    
    return 1;
}


//argv représente le tableau pointant les paramères du programme
//retourne l'indexe de option dans argv. par exemple esi option est 'C'
// la valeur retournée est l'indexe de la chaine "-C" dans argv
// retourne -1 si l'option n'est pas trouvée dans argv
int seek_option(char *const argv[], char option)
{
    int pos = 0;
    while (argv[pos]!='\0')
    {
        if (argv[pos][1]==option)
        {
            return pos;
        }
        pos++;
    }
    
    return -1;
}


//c est soit 'C', soit 'L'.
//dim est censée représenter soit le nombre de lignes dans le tableau 2D soit le nombre de colonnnes.
//argv représente le tableau pointant les paramères du programme.
//retourne un tableau d'entiers de taille dim rempli avec des 0 et des 1 :
//une case est remplie avec 0 si elle correspond à une ligne ou une colonne qui ne va pas
//être supprimée selon argv et l'option c ;
//une case est remplie avec 1 si elle correspond à une ligne ou une colonne qui va
//être supprimée selon argv et l'option c
int * control(char *const argv[], int dim, char c){

    int *tabRetour=calloc(dim,sizeof(int));
        
    int debut;
    int fin;

    int debutDomaines = seek_option(argv, c);
    
    if (debutDomaines==-1)
    {
        return tabRetour;
    }
    
    int nbDomaine = get_nbre_domaines(argv, debutDomaines);
        for (int i = 1; i<=nbDomaine ; i++){
            if (get_debut_fin_domaine(*(argv+(debutDomaines+i)), dim, &debut, &fin))
            {
                for (int j=debut; j<=fin; j++) {
                    tabRetour[j]=1;
                }
            }else{
                signaler_erreur(SYNTAX_DOMAIN_ERREUR);
                exit(1);
            }
        }

    return &(tabRetour[0]);
}

//mat pointe le début d'un tableau 2D de taill *n x *m.
//controlC de taille *m est un vecteur indiquant les colonnes à supprimer selon la fonction control.
//controlV de taille *n est un vecteur indiquant les lignes à supprimer selon la fonction control.
//retourne un pointeur sur le début d'un tableau 2D de la bonne taille après application
// des suppressions données par controlC et controlL  et place la nouvelle taille du tableau dans *n et *m.
//retourne NULL sil le tableau résultant est vide.
int *filter(int * mat, int *n, int *m, int *controlC, int *controlL)
{
    int (*tabAvantFiltre)[*m] = NULL;
    tabAvantFiltre = (int (*)[*m]) mat;
    
    int nbColonneAfficher_C = NbCaseZero(controlC, *m);
    int nbLigneAfficher_L = NbCaseZero(controlL, *n);
    int (*tabFiltre)[nbColonneAfficher_C];
    
    tabFiltre =  malloc(nbLigneAfficher_L*nbColonneAfficher_C*sizeof(int));
    
    if (nbColonneAfficher_C==0 || nbLigneAfficher_L==0) {
        return NULL;
    }
    
    int * controlCincr = controlC;
    int posY=0;
    // incrémente posY et y pour passer de ligne en ligne
    for (int y=0; y < nbLigneAfficher_L; y++, posY++) {
        while (*controlL) {
            posY++;
            controlL++;
        }
        
        int posX = 0;
        // incrémente posX et x pour copier une ligne
        for (int x=0; x < nbColonneAfficher_C; x++, posX++) {
            while(*controlCincr){
                posX++;
                controlCincr++;
            }
            tabFiltre[y][x]= tabAvantFiltre[posY][posX];
            controlCincr++;
        }
        controlCincr = controlC;
        controlL++;
        
    }
    
    *m= nbColonneAfficher_C;
    *n= nbLigneAfficher_L;
    
    return &(tabFiltre[0][0]);
}