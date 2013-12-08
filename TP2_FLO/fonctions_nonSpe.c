/*
 * NOM et Prénom : LASSONDE Pierre-Alexandre
 * Code permanent : LASP16128901
 * NOM et Prénom : BAUMONT Florian
 * Code permanent : BAUF12059008
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "affichage.h"


int *creerVecteur(int *vecteur, FILE *fp)
{
   int *v;
   char c = 0;
   int nbre =0;
   int cpt = 0;
   int nbLus = false;
   int flag = false;
   v = vecteur;

   do
   {
       c=fgetc(fp);
       if (c == ' ' || c == '\n' || c ==EOF)
       {
           nbre = 0;
       }
       else
       {
           nbLus = true;
           flag = true;
           if(!nbre)
           {
               nbre = 1;

               if(nbLus)
               {
                   cpt++;
               }
           }
       }
       if (c == '\n' || c == EOF)
       {
           *v = cpt;
           cpt = 0;
           v++;
       }
       nbLus = false;

   } while (!feof(fp));

   if(!flag)
   {
       signaler_erreur(FICHIER_SANS_DONNEE_ERREUR);
       exit(1);
   }

   return vecteur;
}

int get_nbre_fichier(char  *const argv[], int pos, int argc)

{
    int nbre_fichier = 0;

    while (pos < argc && (strcmp(argv[pos], "-C") && strcmp(argv[pos], "-L")))
    {
        nbre_fichier++;
        pos++;
    }

    return nbre_fichier;
}

/**
 * Verifie si les parametre du programme sont valides
 * @param argc
 * @param argv[]
 * @return false si les parametre sont incorrect et true si les parametre sont valides
 */
int checkOption(int argc, char  *const argv[], int pos)
{
  int erreurOption = true;

  if(argc > 2)
  {
      if (strcmp(argv[pos], "-V") && strcmp(argv[pos], "-H"))
      erreurOption = false;

  }
  else
    erreurOption = false;

  return erreurOption;
}

int get_nbre_lignes(int *vecteur, int nbre_lignes_total)
{
  int nbre_lignes = 0;

  for (int i = 0; i < nbre_lignes_total; i++)
    {
      if (vecteur[i])
        {
          nbre_lignes++;
        }
    }
    return nbre_lignes;
}
