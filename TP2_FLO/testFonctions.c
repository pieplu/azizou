#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "affichage.h"
#include "fonctions.h"

int main(int argc, char *const argv[]) {

  /**
   * Verification des parametres
   *
   */
  int pos = 1;
  int optionValide = checkOption(argc, argv, pos);

  if(!optionValide)
    {
      signaler_erreur(OPTION_ERREUR);
      exit(1);
    }

  /**
   * Creation de la matice compose des differents fichiers
   *
   */
  FILE *fp;

  int nbre_fichier = get_nbre_fichier(argv, 2, argc);
  struct tab2D *vecteurMatrice = remplirMatriceCompose(fp,nbre_fichier, argv);

  struct tab2D matrice_fusion = fusionMatrice(vecteurMatrice, nbre_fichier, argv[1][1]);

  int *controlL = control(argv, matrice_fusion.lignes, 'L');
  int *controlC = control(argv, matrice_fusion.colonnes, 'C');

  struct tab2D matrice_final = {0,0,NULL};
  matrice_final = filter(matrice_fusion, controlC, controlL);

  affiche_Tab2D(matrice_fusion);
  printf("\nDEVIENT :\n\n");
  affiche_Tab2D(matrice_final);

  free(controlL);
  free(controlC);

  free(vecteurMatrice);

  fclose(fp);
  return 0;
}
