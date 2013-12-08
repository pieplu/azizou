#ifndef AFFICHAGE_H
#define AFFICHAGE_H


#define OUVERTURE_FICHIER_ERREUR 0

//Fichier ne comporte aucun mot
#define FICHIER_SANS_DONNEE_ERREUR 1

// Les parm�tres du programmes conformes 
// mais erreur de syntaxe dans l'un des domaines
#define SYNTAX_DOMAIN_ERREUR 2


//Erreur concernant une option
#define OPTION_ERREUR 3

//Le r�sultat est un tableau vide
#define TABLEAU2D_VIDE_ERREUR 4


//Cette structure offre un type de donn�e rep�sentant un tableau 2D
struct tab2D{
int lignes; //nombre de lignes du tableau 2D
int colonnes; //nombre de colonnes du tableau 2D
char* *ptr; // repr�sente un tableau de char* celui est interpr�t� comme
             // un tableau 2D de taille lignes x colonnes
}; 



/**
* affiche une varaible de type struct tab2d
*
*@param mat le tableau 2D � afficher
*/
void affiche_Tab2D(struct tab2D mat);


// cette fonction est fournie
//affiche un message d'erreur sur le canal d'erreur selon les cas d�finis
/**
* Affiche un message d'erreur sur le canal d'erreur selon les cas d�finis
*
*@param err l'erreur � signaler
*/
void signaler_erreur(int err);

#endif