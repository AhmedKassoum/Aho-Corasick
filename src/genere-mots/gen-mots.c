#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "../utilities/utils.h"


// Programme permettant de générer une liste de mots aléatoire selon quatres arguments fournies par l'utilisateur :
//  1) Le nombre de mots à générer.
//	2,3) La longueur minimal et maximal des mots.
//	4) La taille de l'alphabet

int main(int argc, char **argv) {
	if (argc != 5) {
		fprintf(stderr, "Il faut 4 arguments... Nombre de mots à générer, longueur min/max d'un mot et la taille de l'alphabet utilisé");
		return EXIT_FAILURE;
	}

	int cptMots = atoi(argv[1]);
	int tailleMin = atoi(argv[2]);
	int tailleMax = atoi(argv[3]);
	int tailleAlphabet = atoi(argv[4]);

	if (cptMots <= 0) {
		fprintf(stderr, "Taille d'alphabet invalide\n");
		return 1;
	}
	if (tailleMin <= 0) {
		fprintf(stderr, "Taille minimum saisie n'est pas valide.\n");
		return 1;
	}
	if (tailleMax <= 0 || tailleMax < tailleMin) {
		fprintf(stderr, "Taille maximum saisie n'est pas valide.\n");
		return 1;
	}
	if (tailleAlphabet <= 0 || tailleAlphabet > TAILLE_ALPHABET) {
		fprintf(stderr, "Taille de l'alphabet saisie est invalide.\n");
		return 1;
	}

	// Pour ne pas avoir la même seed à chaque exécution.
	srand((unsigned int) time(NULL));

	for (int i = 0; i < cptMots; ++i) {
		int wordLength = (rand() % (tailleMax - tailleMin + 1)) + tailleMin;
		for (int j = 0; j < wordLength; ++j) {
			int r = rand() % tailleAlphabet;
			putchar('!' + r);
		}
		putchar('\n');
	}
	return 0;
}
