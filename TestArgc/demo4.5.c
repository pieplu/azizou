#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compte_c (FILE *f);
int compte_l (FILE *f);
int compte_m (FILE *f);


int main(int argc, char *argv[])
{

FILE *fp ;
int nbre;

printf("%d\n", strcmp(argv[1],"wc") );

if (argc !=4){
printf("nbre d'arguments inccorect \n");
exit(1);
}


if (strcmp(argv[1],"wc") || (strcmp(argv[2],"-l") && strcmp(argv[2],"-w") && strcmp(argv[2],"-c") )){
	printf("erreur de syntaxe ---->  (exemple ./exe wc -l || -c || -w fichier.txt) \n");
	exit(1);
}

fp=fopen(argv[3],"r");

if (!fp)
printf("fichier inexistant \n");

switch (argv[2][1]){
case 'l':
printf("le nombre de ligne est de :%d \n",compte_l(fp) );
break;
case 'w':
printf("le nombre de mot est de :%d \n",compte_m(fp) );
break;
case 'c':
printf("le nombre de caractere est de :%d \n",compte_c(fp) );
break;
case '-':
printf("ho HO ho, c'est le père noel");
break;
}


fclose(fp);

return 0;

}


int compte_c(FILE * f){

int cpt =0;

while (fgetc(f)!=EOF) 
cpt++;

return cpt ;

}

int compte_m (FILE *f){

int c ;
int cpt=0;
int mot=0;

while ((c=fgetc(f))!=EOF)
 if ( c==' ' || c== '\n' ) 
 mot=0; 

 else { 

  if( !mot) {

  mot=1;

  cpt++;

  }

 }

return cpt ;

}


int compte_l (FILE *f){

int c ;

int cpt =0;

while ((c=fgetc(f))!=EOF)

if ( c== '\n'){
	cpt++;
}
cpt++;

return cpt ;

} 