#--------------------------------------
#Declaration de variables
CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lm
#--------------------------------------
PROG = filtre
SRCS = filtre.c fonctions.c affichage.c
#--------------------------------------

#--------------------------------------
#fichiers .o obtenu des .c du meme nom
#--------------------------------------
OBJS = $(SRCS:.c=.o)
#--------------------------------------

#--------------------------------------
#cible de construction du programme
$(PROG) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)
#--------------------------------------

#--------------------------------------
#regles de dependance entre un .o et les .c dont ce .o depend
#--------------------------------------
affichage.o : affichage.c affichage.h
fonctions.o : fonctions.c fonctions.h affichage.h
filtre.o : filtre.c fonctions.h affichage.h

#--------------------------------------
#Utilities
#--------------------------------------
clean:
	/bin/rm -f core *~ $(OBJS)
#--------------------------------------