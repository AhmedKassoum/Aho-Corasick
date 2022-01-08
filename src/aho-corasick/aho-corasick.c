#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ac-matrice.h"
#include "ac-hachage.h"
#include "../utilities/utils.h"
#include <time.h>


// Ce fichier génère deux exécutables selon si oui ou non le macro HACHAGE est défini (inclut dans le makefile)
// Si oui l'exécutable généré est une implantation de l'algo d'aho corasick avec une table de hachage, le cas contraire
// est une implantation du meme algorithme avec une matrice
// Le programme généré prend deux arguments, le premier étant le nom du fichier contenant l'ensemble des mots, le deuxième est le fichier 
// contenant le texte sur lequel effectuer la recherche
int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Arguments manquant...");
		return EXIT_FAILURE;
	}

	FILE *words = fopen(argv[1], "r");
	FILE *text = fopen(argv[2], "r");

	if (words == NULL || text == NULL) {
		fprintf(stderr, "Fichier introuvables...\n");
		return EXIT_FAILURE;
	}

	// Calcul de la longueur maximal d'un mot et le nombre d'état maximum possible
	size_t maxNode = 0;
	size_t maxLen = 0;
	size_t len = 0;
	int chara;
	while ((chara = fgetc(words)) != EOF) {
		if (chara == '\n') {
			if (len > maxLen)
				maxLen = len;
			len = 0;
		}
		len++;
		maxNode++;
	}
	maxLen++; // Prendre en compte le '\0'
	maxNode++;  

	// Création des structures
	#ifdef HACHAGE
	if (maxNode < TAILLE_ALPHABET + 1)
			maxNode = TAILLE_ALPHABET + 1;
		TrieH trieH = createTrieH(maxNode);
		if (trieH == NULL)
			return 1;
	#else
		TrieM  trieM = createTrieM(maxNode);
		if (trieM == NULL)
			return 1;
	#endif

	// Extraction des mots du fichier et remplissage du Trie
	fseek(words, SEEK_SET, 0);
	char word[maxLen];
	while (fgets(word, (int) maxLen, words) != NULL) {
		if (word[0] == '\n')
			continue;
		if (word[strlen(word) - 1] == '\n')
			word[strlen(word) - 1] = '\0';
		#ifdef HACHAGE
			if (insertInTrieH(trieH, word))
				return 1;
		#else
			if (insertInTrieM(trieM, word))
				return 1;
		#endif
	}
	
	// Construction des suppléants et recherche des occurrences
	fseek(words, SEEK_SET, 0);
	size_t cptOcc;
	#ifdef HACHAGE
		createSupH(trieH);
		cptOcc = searchTextH(trieH, text);
	#else
		createSupM(trieM);
		cptOcc = searchTextM(trieM, text);
	#endif

	printf("%ld\n", cptOcc);
	return 0;
}
