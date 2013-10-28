#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(){

	FILE * fichier = NULL;
	fichier = fopen("test02.txt", "r");
	rewind(fichier);

	int temp;
	int nbCarac=0;
	int nblignes=0;
	int nonVide =0;

	do{
		temp=fgetc(fichier);
		while(temp != ' ' && temp != '\n' && temp != EOF){
			temp=fgetc(fichier);
			nonVide=1;
		}

		if(nonVide){
			printf("nbCarac %d - ", ++nbCarac);
		}
		
		if(temp == '\n' || temp == EOF){
		printf("fin de ligne, %d, carac:%d\n", ++nblignes, nbCarac);
		nbCarac=0;
		}

		nonVide=0; //peut être à mettre dans le if du dessus, à voir
	}while(temp != EOF);



	fclose(fichier);

	return 0;
}

