#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../utilities/utils.h"

// Ce programme permet de générer un texte aléatoire selon deux arguments fournis :
// 1) La taille du texte
// 2) La taille de l'alphabét

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Nombre d'arguments invalide...\n");
		return 1;
	}

	int tailleAlphabet = atoi(argv[2]);
	int tailleTexte = atoi(argv[1]);

	if (tailleTexte <= 0) {
		fprintf(stderr, "Taille du texte fournie n'est pas valide...\n");
		return 1;
	}
	if (tailleAlphabet <= 0 || tailleAlphabet > TAILLE_ALPHABET) {
		fprintf(stderr, "Taille de l'alphabet fournie n'est pas valide...\n");
		return 1;
	}

	// Time permet d'assurer un seed différent à chaque exécution
	srand((unsigned int) time(NULL));

	for (int i = 0; i < tailleTexte; ++i) {
		int r = rand() % tailleAlphabet;
		putchar('!' + r);
	}

	return 0;
}
