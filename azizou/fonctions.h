//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

#ifndef TP1
#define TP1
#define true 1
#define false 0

#define OUVERTURE_FICHIER_ERREUR 0

//Fichier ne comporte aucun entier
#define FICHIER_SANS_ENTIER_ERREUR 1

// Les parmètres du programmes conformes
// mais erreur de syntaxe dans l'un des domaines
#define SYNTAX_DOMAIN_ERREUR 2

//Cette erreur indique les paramètres du programme
//ne sont pas conformes au format défini
//Ce cas est autre que la syntax des domaines
#define OPTION_INCONNUE_ERREUR 3

//deux présences ou plus  de -C ou de -L
// -C devrait exister 0 ou 1 fois
// -L devrait exister 0 ou 1 fois
#define OPTION_DUPLIQUEE_ERREUR 4

//Les résultat est un tableau vide
#define TABLEAU2D_VIDE_ERREUR 5

// cette fonction est fournie
//affiche un message d'erreur sur le canal d'erreur selon les cas définis
void signaler_erreur(int err); // fait

// cette fonction est fournie
//affiche un tableau 2D nxm
void affiche_Tab2D(int *ptr, int n, int m); //fait

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
int *charger(FILE *fp, int * vecteur, int taille_vecteur, int max_vecteur);

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



#endif


