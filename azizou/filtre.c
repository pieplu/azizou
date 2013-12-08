//NOM et Prénom : Alexis Piéplu - François Planet
//Code permanent : PIEA07058900 - PLAF17069100

/*
 Le programme filtre sert à filtrer et afficher une matrice contenue dans un fichier
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"
#include "affichage.h"


// retourne un tableau contenant le nombre de caractères de chaques lignes du fichier, igonre les lignes vides
int *creerVecteur(FILE* fichier, int * nbLigne)
{
    rewind(fichier);
    int * nbCharLigne;
    int nombreLigneVecteur = 0;
    nbCharLigne = malloc( (*nbLigne) * sizeof(int));
    int *vecteur = nbCharLigne;
    
    int temp;
	int nbNombres=0;
	int unNbLue =false;
    
	do{
		temp=fgetc(fichier);
		while(temp != ' ' && temp != '\n' && temp != EOF){
			temp=fgetc(fichier);
			unNbLue=true;
		}
        
		if(unNbLue){ ++nbNombres; }
		
		if(temp == '\n' || temp == EOF){
            if(nbNombres != 0){
                *nbCharLigne = nbNombres;
                nbCharLigne++;
                nombreLigneVecteur++;
                nbNombres=0;
            }
		}
		unNbLue=false;
        
	}while(temp != EOF);
    
    rewind(fichier);
    *nbLigne = nombreLigneVecteur;
    return realloc(vecteur , nombreLigneVecteur*sizeof(int));
}




int main(int argc, char * const argv[])
{
    
    FILE * fichier = NULL;
	int *vecteur=NULL;
	char ** ptrTableau2d = NULL;
    char ** ptrTabApresFiltre = NULL;
    int *ControlL = NULL;
    int *ControlC = NULL;
    
    int Cpos = seek_option(argv, 'C');
    int Lpos = seek_option(argv, 'L');
    if (Cpos ==-1 && Lpos == -1 && argc > 2) {
        signaler_erreur(OPTION_ERREUR);
        exit(1);
    }
    int doubleC = seek_option(&argv[Cpos +1 ], 'C');
    int doubleL = seek_option(&argv[Lpos +1 ], 'L');
    if (doubleC != -1 || doubleL != -1) {
        signaler_erreur(OPTION_ERREUR);
        exit(1);
    }
    
    int n;
    int m;
    int nbFichiers = 2;
    stab2d *tableauStructures = malloc(nbFichiers*sizeof(stab2d));
    stab2d unTableau;
    for (int i=0; i<nbFichiers; i++) {
        fichier = fopen(argv[(i+1)], "r");
        if(fichier == NULL)	{
            signaler_erreur(OUVERTURE_FICHIER_ERREUR);
            exit(1);
        }
        
        n =nbre_lignes_fichier(fichier);
        vecteur = creerVecteur(fichier, &n);
        m = taille_max_lignes(vecteur, n);
        if(!m)	{
            signaler_erreur(FICHIER_SANS_DONNEE_ERREUR);
            exit(1);
        }

        
        unTableau.ptr = charger(fichier, vecteur, n, m);
        unTableau.lignes = n;
        unTableau.colonnes = m;
        tableauStructures[i] = unTableau;
        fclose(fichier);

    }
    
    
    
    
    stab2d tabFusion = tableauStructures[0];
    ControlL = control(argv, n, 'L');
    ControlC = control(argv, m, 'C');
    
  //  ptrTabApresFiltre = filter(ptrTableau2d, &n, &m, ControlC, ControlL);
    

    affiche_Tab2D(tabFusion);
    affiche_Tab2D(tableauStructures[1]);
    
	
	free(vecteur);
    free(ptrTableau2d);
    free(ptrTabApresFiltre);
    free(ControlC);
    free(ControlL);
	   
    return 0;
}

