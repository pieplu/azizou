#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(){

	FILE * fichier = NULL;
	fichier = fopen("test01.txt", "r");
	rewind(fichier);

	int Nombre;
	int temp;
	int nbCarac;

	do{
		nbCarac = 0;
		Nombre=0;
		temp=fgetc(fichier);
		while(temp != ' ' && temp != '\n' && temp != EOF){
			Nombre = Nombre*10 + (temp-'0');
			temp=fgetc(fichier);
		}
		printf(" %d\n", Nombre);
		nbCarac++;

		if(temp == '\n' || temp == EOF){
		printf("fin de ligne, %d", nbCarac);

		}
	}while(temp != EOF);

printf("sorti");

	fclose(fichier);

	return 0;
}

