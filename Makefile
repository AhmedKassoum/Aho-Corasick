# Aho-corasick
REPAC = src/aho-corasick/
OBJAC = $(REPAC)aho-corasick.o
OBJACM = $(REPUTIL)utils.o $(REPAC)ac-matrice.o
OBJACH = $(REPUTIL)utils.o $(REPAC)ac-hachage.o

# Génération de mots
REPGENM = src/genere-mots/
OBJGENM = $(REPGENM)gen-mots.o

# Génération de texte
REPGENT = src/genere-texte/
OBJGENT = $(REPGENT)gen-texte.o

REPUTIL = src/utilities/

CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -I$(REPUTIL) -I$(REPGENT) -I$(REPGENM) -I$(REPAC)
PROGRAMS = ac-matrice ac-hachage genere-texte genere-mots
OBJ = $(OBJAC) $(OBJACM) $(OBJACH) $(OBJGENM) $(OBJGENT)

all: ac-matrice ac-hachage genere-texte genere-mots

genere-texte: $(OBJGENT)
	$(CC) $(OBJGENT) $(CFLAGS) -o genere-texte

genere-mots: $(OBJGENM)
	$(CC) $(OBJGENM) $(CFLAGS) -o genere-mots

ac-hachage: $(OBJACH)
	$(CC) $(CFLAGS) -c -o $(REPAC)aho-corasick.o $(REPAC)aho-corasick.c -DHACHAGE
	$(CC) $(OBJACH) $(OBJAC) $(CFLAGS) -o ac-hachage

ac-matrice: $(OBJACM)
	$(CC) $(CFLAGS) -c -o $(REPAC)aho-corasick.o $(REPAC)aho-corasick.c 
	$(CC) $(OBJACM) $(OBJAC) $(CFLAGS) -o ac-matrice

clean:
	@rm -rf $(OBJ) $(PROGRAMS)



