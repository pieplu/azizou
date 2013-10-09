//NOM et Prénom : 
//Code permanent :

#include <stdio.h>
#include "fonctions.h"
#include <stdlib.h>

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
