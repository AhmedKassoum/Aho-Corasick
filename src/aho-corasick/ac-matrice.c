#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../utilities/utils.h"
#include "ac-matrice.h"

// On défini la matrice de transitions comme un tableau de pointeur.
// Chacun de ces tableau représente un état et chaque colonne une lettre.

TrieM createTrieM(size_t maxNode)
{
	TrieM trieM = malloc(sizeof *trieM);
	if (trieM == NULL)
		return NULL;
	trieM->nextNode = 1;
	trieM->maxNode = maxNode;
	trieM->transition = malloc(sizeof(int *) * maxNode);
	if (trieM->transition == NULL)
		return NULL;
	int *node = calloc(TAILLE_ALPHABET, sizeof(int));
	if (node == NULL)
		return NULL;
	trieM->transition[0] = node;
	for (size_t i = 1; i < maxNode; i++)
	{
		int *node = malloc(sizeof(int) * TAILLE_ALPHABET);
		if (node == NULL)
			return NULL;

		for (int j = 0; j < TAILLE_ALPHABET; j++)
		{
			node[j] = -1;
		}
		trieM->transition[i] = node;
	}

	trieM->sup = malloc(maxNode * sizeof(int));
	if (trieM->sup == NULL)
		return NULL;
	for (size_t i = 0; i < maxNode; i++)
	{
		trieM->sup[i] = -1;
	}

	trieM->finite = calloc(maxNode, sizeof(int));
	if (trieM->finite == NULL)
		return NULL;

	return trieM;
}

int insertInTrieM(TrieM trieM, const char *word)
{
	int currentNode = 0;
	for (size_t i = 0; i < strlen(word); ++i)
	{
		char c = word[i];
		int rangLettre = c - DEBUT_ALPHABET;
		// La liaison n'existe pas, on écrit dans la matrice
		if (trieM->transition[currentNode][rangLettre] == -1 || (currentNode == 0 && trieM->transition[currentNode][rangLettre] == 0))
		{
			trieM->transition[currentNode][rangLettre] = trieM->nextNode;
			currentNode = trieM->nextNode;
			trieM->nextNode++;
			// La liaison existe déja, on trieMoursuit
		}
		else
		{
			currentNode = trieM->transition[currentNode][rangLettre];
		}
	}
	trieM->finite[currentNode] = 1;
	return 0;
}

int createSupM(TrieM trieM)
{
	queue *q = createQueue(trieM->maxNode);
	if (q == NULL)
		return -1;
	// Initialisation des suppleants de l'état racine et les états de niveau 1
	for (int i = 0; i < TAILLE_ALPHABET; ++i)
	{
		if (trieM->transition[0][i] != -1 && trieM->transition[0][i] != 0)
		{
			trieM->sup[trieM->transition[0][i]] = 0;
			pushQueue(q, trieM->transition[0][i]);
		}
	}
	// Remplissage des suppleants pour les états de niveau > 1
	while (sizeQueue(q))
	{
		int node = popQueue(q);
		for (int i = 0; i < TAILLE_ALPHABET; ++i)
		{
			if (trieM->transition[node][i] != -1)
			{
				int sup = trieM->sup[node];
				while (trieM->transition[sup][i] == -1)
				{
					sup = trieM->sup[sup];
				}
				sup = trieM->transition[sup][i];
				trieM->sup[trieM->transition[node][i]] = sup;
				pushQueue(q, trieM->transition[node][i]);
			}
		}
	}
	return 0;
}

size_t searchTextM(TrieM trieM, FILE *text)
{
	size_t cptMots = 0;
	int currentNode = 0;
	int c;
	// Boucle permettant de lire le contenu du fichier caractere par caractere
	while ((c = fgetc(text)) != EOF)
	{
		if (c < DEBUT_ALPHABET || c > FIN_ALPHABET)
			continue;
		c = c - DEBUT_ALPHABET;
		// Tant que le noeud n'a pas de transition avec le caractère courrant, on remonte
		// à son suppleant jusqu'a trouver un état qui a une transition avec ce caractère ou
		// arriver à l'état initial et dans e cas on aura forcémment une transition
		while (trieM->transition[currentNode][c] == -1)
		{
			currentNode = trieM->sup[currentNode];
			// Il se peut que l'état vers lequel on remonte soit un état final,
			// s'il l'est, ceci veut dire qu'on a trouvé une occurence d'un des mots de
			// l'ensemple dans le texte, donc on incrémente le compteur d'occurences
			if (trieM->finite[currentNode] == 1)
				cptMots++;
		}
		currentNode = trieM->transition[currentNode][c];

		// Vérification si l'état courrant est un état final, c.a-d, on a trouvé une
		// occurence de l'un des mots de l'esemble dans le texte
		if (trieM->finite[currentNode] == 1)
			cptMots++;
	}
	return cptMots;
}
