//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#ifndef FONCTIONS_H
#define FONCTIONS_H
#define true 1
#define false 0

typedef struct tab2D stab2d;


/*
 * retourne le nombre de lignes total du fichier pointé par fp
 * Compatible avec les fichier dans '\n' sur leur dernière ligne (sous sublime text, MacOsX...)
 * Retourne une ligne de plus pour les autres (sous Linux/Unix, Windows ...)
 *@param fp   : le fichier
 *@return le nombre de lignes
 */
int nbre_lignes_fichier(FILE *fp);

/*
 *retourne la plus haute valeur des case du tableau vecteur
 *@param vecteur        : le tableau
 *@param v : taille du tableau vecteur
 *@return la plus haute valeur ou 0 si le tableau est vide (NULL)
 */
int taille_max_lignes(int * vecteur , int v); //fait

/*
 *retourne le nombre de case contenant 0 dans un tableau
 *@param vecteur        : le tableau
 *@param taille_vecteur : taille du tableau vecteur
 *@return le nombre de case contenant 0
 */
int NbCaseZero(int *vecteur, int taille_vecteur);

/*
 *Cette fonction retourne un pointeur sur la première case d'un tableau 2D n x m
 *Chaque ligne du fichier qui contient au moins un entier donne lieu à une ligne dans le tableau 2D
 *@param vecteur        : tableau du nombre d'entiers du fichier pointé par fp.
 *@param fp             : fichier à charger
 *@param taille_vecteur : taille du tableau vecteur
 *@param max_vecteur    : plus haute valeur présente dans vecteur, et donc largeur du tableau 2D
 *@return la taille de la liste
 */
char **charger(FILE *fp, int * vecteur, int taille_vecteur, int max_vecteur);

/*
 *Verifie si un domaine est syntaxiquement correcte
 *@param domaine   : le pointeur de chaine de caractère du domaine
 *@return 1 si correcte et 0 sinon
 */
int check_domaine(char *domaine) ;


/*
 *Cette fonction retourne la taille de la liste de domaines à partir argv[pos]
 *@param argv   : le tableau des paramères du programme
 *@param pos    : représenter l'indice de l'option dans argv
 *@return la taille de la liste
 */
int get_nbre_domaines(char  *const argv[], int pos);

/*
 *retourne 1 ou 0, en fonction de la syntaxe du domaine soit correcte ou non.
 *et place le début et la fin du domaine dans debut et fin
 *@param max        : est utilisé pour que <nun>- represente le domaine <num>-max
 *@param debut      : début du dommaine à setter
 *@param fin        : fin du dommaine à setter
 *@param domaine    : chaine de caractère du domaine
 *@return 1 pour domaine correct et 0 pour dommaine incorect
 */
int get_debut_fin_domaine(char * domaine, int max, int *debut, int *fin);

/*
 *Fusione toutes les matrice présente dans le tableau passer en paramère
 *@param argv   : tableau pointant les paramères du programme
 *@param option : option à charcher dans argv
 *@return l'indexe de option dans argv ou -1 si l'option n'est pas trouvée dans argv
 */
int seek_option(char *const argv[], char option);

/*
 *Fusione toutes les matrice présente dans le tableau passer en paramère
 *@param tabMatrices : Tableau des matrices à fusionner
 *@param nbMatrice   : Nombre de matrices du tableau
 *@param option      : V (fusion Vertical) ou H (fusion Horizontal)
 *@return une nouvelle structure contant la fusion des matrices
 */
stab2d fusionMatrices(stab2d *tabMatrices, int nbMatrices, char option);


/*
 *Defini la taille de la matrice finale apres fusion
 *@param *hauteur : Tableau des matrices à fusionner
 *@param *largeur   : Nombre de matrices du tableau
 *@param option      : V (fusion Vertical) ou H (fusion Horizontal)
 *@return une nouvelle structure contant la fusion des matrices
 */
void tailleMatriceFinale(int* hauteur, int* largueur, stab2d *tabMatrices, int nbMatrices, char option);

/*
 *retourne un tableau d'entiers de taille dim rempli avec des 0 et des 1 :
 *une case est remplie avec 0 si elle correspond à une ligne ou une colonne qui ne va pas
 *et avec 1 si elle correspond à une ligne ou une colonne qui va être supprimée
 *@param c      : soit 'C', soit 'L'.
 *@param dim    : Taille de la zone à controlé (soit ligne, soit collone du tableau)
 *@param option : V (fusion Vertical) ou H (fusion Horizontal)
 *@return l'adresse du tableau setter de 0 ou 1
 */
int * control(char *const argv[], int dim, char c);


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
char** filter(char** mat, int *n, int *m, int *controlC, int *controlL);


#endif


