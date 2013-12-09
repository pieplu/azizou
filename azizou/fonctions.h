//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#ifndef FONCTIONS_H
#define FONCTIONS_H
#define true 1
#define false 0
typedef struct tab2D stab2d;

// cette fonction est fournie
//affiche un message d'erreur sur le canal d'erreur selon les cas définis
void signaler_erreur(int err); // fait


// retourne le nombre de lignes total du fichier pointé par fp
int nbre_lignes_fichier(FILE *fp); //fait

// retourne le max du tableau pointé par vecteur et de taille v
// retourne 0 si le tableau est vide (NULL)
int taille_max_lignes(int * vecteur , int v); //fait

//vecteur[i] représente le nombre d'entiers à ligne i du fichier pointé par fp.
//si vecteur[i]==0, la ligne i du fichier est ignorée car elle est vide d'entier.
//Cette fonction retourne un pointeur sur la première case d'un tableau 2D n x m
//Le tableau 2D de taille n x max_veteur est rempli à partir du fichier.
//Chaque ligne du fichier qui contient au moins un entier donne lieu à une ligne dans le tableau 2D.
char **charger(FILE *fp, int * vecteur, int taille_vecteur, int max_vecteur);

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
char** filter(char** mat, int *n, int *m, int *controlC, int *controlL);


#endif


