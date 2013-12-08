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

int nbre_lignes_fichier(FILE *fp)
{
    int c;
    int nbLigne = 0;

    while (!feof(fp))
    {
        c=fgetc(fp);
        if (c == '\n' || c == EOF)
        {
            nbLigne++;
        }
    }
    return nbLigne;
}

int taille_max_lignes(int * vecteur , int v)
{
    if (vecteur == NULL)
    {
        return 0;
    }
        
    int max = 0;

    for (int i = 0; i < v; i++)
    {
        if (max < vecteur[i])
        {
            max = vecteur[i];
        }
    }
    return max;
}



struct tab2D *remplirMatriceCompose(FILE * fp, int nbre_fichier, char  *const argv[])
{
  struct tab2D *vecteurMatrice = malloc(nbre_fichier * sizeof(struct tab2D));
  for (int i = 0; i < nbre_fichier; ++i)
  {
      fp = fopen(argv[i+2],"r");
      if (!fp)
      {
          signaler_erreur(OUVERTURE_FICHIER_ERREUR);
          exit(1);
      }

      struct tab2D courant = {0,0,NULL};
      int nbre_lignes_total = nbre_lignes_fichier(fp);
      rewind(fp);

      int *vecteurOccurence = calloc(nbre_lignes_total, sizeof(int));
      vecteurOccurence = creerVecteur(vecteurOccurence, fp);
      rewind(fp);

      courant.colonnes = taille_max_lignes(vecteurOccurence, nbre_lignes_total);
      courant.lignes = get_nbre_lignes(vecteurOccurence, nbre_lignes_total);

      char **p = charger(fp, vecteurOccurence, nbre_lignes_total, courant.colonnes);

      courant.ptr = p;
      rewind(fp);

      vecteurMatrice[i] = courant;

      free(vecteurOccurence);
  }

  return vecteurMatrice;
}

struct tab2D fusionMatrice(struct tab2D *vecteurMatrice, int nbre_fichier, char option)
{
    int nbc = 0;
    int nbl = 0;
    int max = 0;
    int maxl = 0;

    if (option == 'V')
    {
        for (int i = 0; i < nbre_fichier; ++i) {

            nbl += vecteurMatrice[i].lignes;

            if (max < vecteurMatrice[i].colonnes)
            {
                max = vecteurMatrice[i].colonnes;
            }
        }
        nbc = max;
    }
    else if (option == 'H')
    {
        for (int i = 0; i < nbre_fichier; ++i) {

            nbc += vecteurMatrice[i].colonnes;

            if (maxl < vecteurMatrice[i].lignes)
            {
                maxl = vecteurMatrice[i].lignes;
            }
        }
        max = nbc;
        nbl = maxl;
    }
    else
    {
        signaler_erreur(3);
        exit(1);
    }

    char *(*ptrtab2d)[max] = NULL;
    ptrtab2d = malloc((max * nbl) * (sizeof(char *)));
    int pos = 0;
    int cpt = 0;

    if (option == 'H')
    {
        for (int x = 0; x < nbre_fichier; ++x)
        {
            for (int i = 0; i < nbl; ++i)
            {
                for (int j = 0; j < vecteurMatrice[x].colonnes; ++j)
                {
                    if (i < vecteurMatrice[x].lignes)
                    {
                        ptrtab2d[i][j+pos] = vecteurMatrice[x].ptr[cpt];
                        cpt++;
                    }
                    else
                    {
                        ptrtab2d[i][j+pos] = "";
                    }
                }
            }
            cpt = 0;
            pos += vecteurMatrice[x].colonnes;
        }
    }
    else if (option == 'V')
    {
        for (int x = 0; x < nbre_fichier; ++x)
        {
            for (int i = 0; i < nbl; ++i)
            {
                for (int j = 0; j < nbc; ++j)
                {
                    if (j < vecteurMatrice[x].colonnes)
                    {
                        ptrtab2d[i+pos][j] = vecteurMatrice[x].ptr[cpt];
                        cpt++;
                    }
                    else
                    {
                        ptrtab2d[i+pos][j] = "";
                    }
                }
            }
            cpt = 0;
            pos += vecteurMatrice[x].lignes;
        }
    }

    struct tab2D matrice_fusion;
    matrice_fusion.colonnes = nbc;
    matrice_fusion.lignes = nbl;
    matrice_fusion.ptr = &ptrtab2d[0][0];

    return matrice_fusion;
}

char **charger(FILE *fp, int * vecteur, int taille_vecteur, int max_vecteur)
{
    int cptLigne = 0;
        char elem[256];
    int cpt = 0;
    char *(*ptrtab2d)[max_vecteur] = NULL;

    for (int i = 0; i < taille_vecteur; ++i)
    {
                if (vecteur[i])
        {
            cptLigne++;
        }
    }

    ptrtab2d = malloc((cptLigne * max_vecteur) * (sizeof(char*)));
    int tab[cptLigne];

    for (int i = 0; i < taille_vecteur; ++i)
    {
        if (vecteur[i])
        {
            tab[cpt] = vecteur[i];
            cpt++;
        }
    }

    for (int i = 0; i < cptLigne; ++i)
    {
        for (int j = 0; j < max_vecteur; ++j)
        {
            if (j < tab[i])
            {
                fscanf(fp, "%s", elem);
                ptrtab2d[i][j] = strcpy(malloc(sizeof(elem)),elem);
            }
            else
            {
                ptrtab2d[i][j] = "";
            }
        }
    }
    return &(ptrtab2d[0][0]);
}

int get_nbre_domaines(char  *const argv[], int pos)
{
    int cpt = 0;
    int i = 0;
    int flagL = 0;
    int flagC = 0;

    while (argv[i] != NULL)
    {
        if (!strcmp(argv[i], "-L"))
        {
            if (flagL == 1)
            {
                signaler_erreur(OPTION_ERREUR);
                exit(1);
            }
            flagL = 1;
        }
        if (!strcmp(argv[i], "-C"))
        {
            if (flagC == 1)
            {
                signaler_erreur(OPTION_ERREUR);
                exit(1);
            }
            flagC = 1;
        }
        i++;
    }

    i = 1;
    while (argv[pos+i] != NULL)
    {
        if (strcmp(argv[pos+i], "-L") && strcmp(argv[pos+i], "-C"))
        {
            cpt++;
            i++;
        }
        else
        {
            return cpt;
        }
    }
    return cpt;
}

int check_domaine(char *domaine)
{
    char *ptr = domaine;
    int flagT = 0;
    int flagN = 0;

    while(*ptr != '\0')
    {
        if ((*ptr >= '0' && *ptr <= '9') || *ptr == '-')
        {
            if (*ptr >= '0' && *ptr <= '9')
            {
                flagN = 1;
            }
            if (*ptr == '-')
            {
                if (flagT)
                {
                    return 0;
                }
                flagT += 1;
            }
        }
        else
        {
            return 0;
        }
        ptr++;
    }
    if (flagN == 0)
    {
        return 0;
    }
    return 1;
}

int get_debut_fin_domaine(char * domaine, int max, int *debut, int *fin)
{
    int cpt = 0;
    int tailleDomaine = 0;
    int nbr;
    char *ptr = domaine;
    int flagNombre = 0;
    int flagT = 0;

    if (!check_domaine(domaine))
    {
        return 0;
    }

    while(*ptr != '\0')
    {
        tailleDomaine ++;
        if (*ptr == '-')
        {
            flagT = 1;
        }
        ptr++;
    }
    ptr = domaine;

    if (flagT == 0)
    {
        while(*ptr != '\0')
        {
            if(flagNombre == 1)
            {
                nbr = nbr * 10 + (int)(*ptr - '0');
            }
            if (flagNombre == 0)
            {
                nbr = (int)(*ptr - '0');
                flagNombre = 1;
            }

            ptr++;
        }
        *debut = nbr;
        *fin = nbr;

        return 1;
    }
    ptr = domaine;
    flagNombre = 0;

    if (*ptr == '-')
    {
        *debut = 0;
        ptr++;
        while(*ptr != '\0')
        {
            if(flagNombre == 1)
            {
                nbr = nbr * 10 + (int)(*ptr - '0');
            }
            if (flagNombre == 0)
            {
                nbr = (int)(*ptr - '0');
                flagNombre = 1;
            }
            ptr++;
        }
        *fin = nbr;

        return 1;
    }

    ptr = domaine;
    flagNombre = 0;

    while(*ptr != '\0')
    {
        if (*ptr == '-' && cpt == tailleDomaine-1)
        {
            ptr = domaine;
            while(*ptr != '-')
            {
                if(flagNombre == 1)
                {
                    nbr = nbr * 10 + (int)(*ptr - '0');
                }
                if (flagNombre == 0)
                {
                    nbr = (int)(*ptr - '0');
                    flagNombre = 1;
                }
                ptr++;
            }
            *debut = nbr;
            *fin = max;
            return 1;
        }
        ptr++;
        cpt++;
    }

    ptr = domaine;
    flagNombre = 0;

    while(*ptr != '\0')
    {
        if (*ptr == '-')
        {
            *debut = nbr;
            nbr = 0;
            flagNombre = 0;
            ptr++;
            while(*ptr != '\0')
            {
                if(flagNombre == 1)
                {
                    nbr = nbr * 10 + (int)(*ptr - '0');
                }
                else
                {
                    nbr = (int)(*ptr - '0');
                    flagNombre = 1;
                }
                    ptr++;
            }
            *fin = nbr;
            return 1;
        }
        if(flagNombre == 1)
        {
            nbr = nbr * 10 + (int)(*ptr - '0');
        }
        else
        {
            nbr = (int)(*ptr - '0');
            flagNombre = 1;
        }
        ptr++;
    }
    return 1;
}

int seek_option(char *const argv[], char option)
{
    int i = 0;

    while(argv[i] != NULL)
    {
        if (argv[i][1] == option)
        {
            return i;
        }
        i++;
    }
    return -1;
}

int * control(char *const argv[], int dim, char c)
{
    int deb =0;
    int fn =0;
    int *debut = &deb;
    int *fin = &fn;
    int *vecteurC = calloc(dim, sizeof(int));
    int index = 0;
    index = seek_option(argv, c);

    if (index == -1)
    {
        return vecteurC;
    }

    int nbreDomaines = 0;
    nbreDomaines = get_nbre_domaines(argv, index);

    for (int i = 0; i < nbreDomaines; i++)
    {
        if (get_debut_fin_domaine(argv[index + i + 1], dim, debut, fin))
        {
            for (int j = *debut; j <= *fin && j < dim ; j++)
            {
                vecteurC[j] = 1;
            }
        }
        else
        {
            signaler_erreur(2);
            exit(1);
        }
    }
    return vecteurC;
}

struct tab2D filter(struct tab2D matrice_fusion, int *controlC, int *controlL)
{
    int matrice2_nbre_lignes = 0;
    int matrice2_nbre_colonnes = 0;
    int cpt = 0;

    for (int i = 0; i < matrice_fusion.colonnes; i++)
    {
        if (!controlC[i])
        {
            matrice2_nbre_colonnes++;
        }
    }

    for (int i = 0; i < matrice_fusion.lignes; i++)
    {
        if (!controlL[i])
        {
            matrice2_nbre_lignes++;
        }
    }

    char * (*ptrtab2d)[matrice2_nbre_colonnes] = NULL;
    ptrtab2d = malloc((matrice2_nbre_lignes * matrice2_nbre_colonnes) * (sizeof(char)));

    char * (*lignePtr)[matrice_fusion.colonnes] = NULL;
    lignePtr = (char * (*)[matrice_fusion.colonnes]) matrice_fusion.ptr;

    char **nouvemat = malloc((matrice2_nbre_colonnes * matrice2_nbre_lignes) * sizeof(char));

    for (int i = 0; i < matrice_fusion.lignes; i++)
    {
        if (!controlL[i])
        {
            for (int j = 0; j < matrice_fusion.colonnes; j++)
            {
                if (!controlC[j])
                {
                    nouvemat[cpt] = lignePtr[i][j];
                    cpt++;
                }
            }
        }
    }

    cpt = 0;

    for (int i = 0; i < matrice2_nbre_lignes; ++i)
    {
        for (int j = 0; j < matrice2_nbre_colonnes; ++j)
        {
            ptrtab2d[i][j] = nouvemat[cpt];
            cpt++;
        }
    }

    struct tab2D matrice2 = {0,0,NULL};
    matrice2.ptr = &ptrtab2d[0][0];
    matrice2.lignes = matrice2_nbre_lignes;
    matrice2.colonnes = matrice2_nbre_colonnes;

    return matrice2;
}


