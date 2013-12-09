//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "affichage.h"



/*
 * retourne le nombre de lignes total du fichier pointé par fp
 * Compatible avec les fichier dans '\n' sur leur dernière ligne (sous sublime text, MacOsX...)
 * Retourne une ligne de plus pour les autres (sous Linux/Unix, Windows ...)
 *@param fp   : le fichier
 *@return le nombre de lignes
 */
int nbre_lignes_fichier(FILE *fp)
{
    int nbLigne=1;
    char c = 0;
    if(fp != NULL){
        while (c != EOF){
            c = fgetc(fp);
            if (c == '\n'){
                nbLigne++;
            }
        }
    }
    rewind(fp);
    return nbLigne;
}


/*
 *retourne la plus haute valeur des case du tableau vecteur
 *@param vecteur        : le tableau
 *@param v : taille du tableau vecteur
 *@return la plus haute valeur ou 0 si le tableau est vide (NULL)
 */
int taille_max_lignes(int * vecteur , int v){
    int maxVal=0;
    for(int i=0; i < v; i++){
        maxVal = *(vecteur + i)>maxVal ? *(vecteur + i) : maxVal;
    }
    return maxVal;
}



/*
 *retourne le nombre de case contenant 0 dans un tableau
 *@param vecteur        : le tableau
 *@param taille_vecteur : taille du tableau vecteur
 *@return le nombre de case contenant 0
 */
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



/*
 *Cette fonction retourne un pointeur sur la première case d'un tableau 2D n x m
 *Chaque ligne du fichier qui contient au moins un entier donne lieu à une ligne dans le tableau 2D
 *@param vecteur        : tableau du nombre d'entiers du fichier pointé par fp.
 *@param fp             : fichier à charger
 *@param taille_vecteur : taille du tableau vecteur
 *@param max_vecteur    : plus haute valeur présente dans vecteur, et donc largeur du tableau 2D
 *@return la taille de la liste
 */
char **charger(FILE *fp, int * vecteur, int taille_vecteur, int max_vecteur)
{
    char curElem[100];
    char *(*tableau2dim)[max_vecteur];
    tableau2dim=calloc(max_vecteur*taille_vecteur,sizeof(char *));

    for (int y = 0; y < taille_vecteur; y++){
        for (int x = 0; x < max_vecteur; x++){
            if(x < *vecteur){
                fscanf (fp, "%s", curElem);
                tableau2dim[y][x] = strcpy(calloc(1,strlen(curElem)+1),curElem);
            }else{
                tableau2dim[y][x] = "";
            }
        }
        vecteur++;
    }
    
    rewind(fp);
    return &(tableau2dim[0][0]);
}


/*
 *Verifie si un domaine est syntaxiquement correcte
 *@param domaine   : le pointeur de chaine de caractère du domaine
 *@return 1 si correcte et 0 sinon
 */
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



/*
 *Cette fonction retourne la taille de la liste de domaines à partir argv[pos]
 *@param argv   : le tableau des paramères du programme
 *@param pos    : représenter l'indice de l'option dans argv
 *@return la taille de la liste
 */
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




/*
 *retourne 1 ou 0, en fonction de la syntaxe du domaine soit correcte ou non.
 *et place le début et la fin du domaine dans debut et fin
 *@param max        : est utilisé pour que <nun>- represente le domaine <num>-max
 *@param debut      : début du dommaine à setter
 *@param fin        : fin du dommaine à setter
 *@param domaine    : chaine de caractère du domaine
 *@return 1 pour domaine correct et 0 pour dommaine incorect
 */
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



/*
 *Fusione toutes les matrice présente dans le tableau passer en paramère
 *@param argv   : tableau pointant les paramères du programme
 *@param option : option à charcher dans argv
 *@return l'indexe de option dans argv ou -1 si l'option n'est pas trouvée dans argv
 */
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

/*
 *Fusione toutes les matrice présente dans le tableau passer en paramère
 *@param tabMatrices : Tableau des matrices à fusionner
 *@param nbMatrice   : Nombre de matrices du tableau
 *@param option      : V (fusion Vertical) ou H (fusion Horizontal)
 *@return une nouvelle structure contant la fusion des matrices
 */
stab2d fusionMatrices(stab2d *tabMatrices, int nbMatrices, char option){
    
    int nbColonnesFusion = 0;
    int nbLignesFusion = 0;
    
    tailleMatriceFinale(&nbLignesFusion, &nbColonnesFusion, tabMatrices, nbMatrices, option);
    
    char *(*tableau2dim)[nbColonnesFusion] = NULL;
    tableau2dim = malloc(nbColonnesFusion * nbLignesFusion * (sizeof(char *)));
    int positionDansFusion = 0;
    int pointeurAlire = 0;
    
    
    switch (option) {
        case 'H':
            for (int ptrMatrices = 0; ptrMatrices < nbMatrices; ptrMatrices++){
                for (int ptrLignes = 0; ptrLignes < nbLignesFusion; ptrLignes++){
                    for (int ptrCol = 0; ptrCol < tabMatrices[ptrMatrices].colonnes; ptrCol++){
                        
                        if (ptrLignes < tabMatrices[ptrMatrices].lignes){
                            tableau2dim[ptrLignes][ptrCol+positionDansFusion] = tabMatrices[ptrMatrices].ptr[pointeurAlire];
                            pointeurAlire++;
                        }
                        else{
                            tableau2dim[ptrLignes][ptrCol+positionDansFusion] = "";
                        }
                    }
                }
                positionDansFusion += tabMatrices[ptrMatrices].colonnes;
                pointeurAlire = 0;
            }

            break;
            
        case 'V':
            for (int ptrMatrices = 0; ptrMatrices < nbMatrices; ptrMatrices++){
                for (int ptrLignes = 0; ptrLignes < nbLignesFusion; ptrLignes++){
                    for (int ptrCol = 0; ptrCol < nbColonnesFusion; ptrCol++){
                        
                        if (ptrCol < tabMatrices[ptrMatrices].colonnes){
                            tableau2dim[ptrLignes+positionDansFusion][ptrCol] = tabMatrices[ptrMatrices].ptr[pointeurAlire];
                            pointeurAlire++;
                        }
                        else{
                            tableau2dim[ptrLignes+positionDansFusion][ptrCol] = "";
                        }
                    }
                }
                pointeurAlire = 0;
                positionDansFusion += tabMatrices[ptrMatrices].lignes;
            }

            break;
    }
    
    stab2d matriceFusione = {nbLignesFusion,nbColonnesFusion,&tableau2dim[0][0]};
    return matriceFusione;
}

/*
 *Defini la taille de la matrice finale apres fusion
 *@param *hauteur : Tableau des matrices à fusionner
 *@param *largeur   : Nombre de matrices du tableau
 *@param option      : V (fusion Vertical) ou H (fusion Horizontal)
 *@return une nouvelle structure contant la fusion des matrices
 */

void tailleMatriceFinale(int* hauteur, int* largueur, stab2d *tabMatrices, int nbMatrices, char option)
{
    for (int i = 0; i < nbMatrices; i++)
    {
        switch (option) {
            case 'H':
                if (tabMatrices[i].colonnes > *hauteur){
                    *hauteur = tabMatrices[i].lignes;
                }
                *largueur += tabMatrices[i].colonnes;
                break;
            case 'V':
                if (tabMatrices[i].colonnes > *largueur){
                    *largueur = tabMatrices[i].colonnes;
                }
                *hauteur += tabMatrices[i].lignes;
                break;
            default:
                signaler_erreur(SYNTAX_DOMAIN_ERREUR);
                exit(1);
        }
    }
}



/*
 *retourne un tableau d'entiers de taille dim rempli avec des 0 et des 1 :
 *une case est remplie avec 0 si elle correspond à une ligne ou une colonne qui ne va pas
 *et avec 1 si elle correspond à une ligne ou une colonne qui va être supprimée
 *@param c      : soit 'C', soit 'L'.
 *@param dim    : Taille de la zone à controlé (soit ligne, soit collone du tableau)
 *@param option : V (fusion Vertical) ou H (fusion Horizontal)
 *@return l'adresse du tableau setter de 0 ou 1
 */
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



/*
 *retourne un pointeur sur le début d'un tableau 2D de la bonne taille après application
 *des suppressions données par controlC et controlL  et place la nouvelle taille du tableau dans *n et *m.
 *@param m          : taille de controlC
 *@param n          : taille de controlL
 *@param controlC   : vecteur indiquant les colonnes à supprimer selon la fonction control.
 *@param controlL   : vecteur indiquant les lignes à supprimer selon la fonction control.
 *@param mat        : pointe le début d'un tableau 2D de taill *n x *m.
 *@return le pointeur ou NULL si le tableau résultant est vide.
 */
char** filter(char** mat, int *n, int *m, int *controlC, int *controlL)
{
    char* (*tabAvantFiltre)[*m] = NULL;
    tabAvantFiltre = (char* (*)[*m]) mat;
    
    int nbColonneAfficher_C = NbCaseZero(controlC, *m);
    int nbLigneAfficher_L = NbCaseZero(controlL, *n);
    char* (*tabFiltre)[nbColonneAfficher_C];
    
    tabFiltre =  malloc(nbLigneAfficher_L*nbColonneAfficher_C*sizeof(char*));
    
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