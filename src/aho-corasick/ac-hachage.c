#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../utilities/utils.h"
#include "ac-hachage.h"

// Fonction de hachage qui prend en paramètre l'état
// actuel et la lettre voulu

int insertLast(List liste, int startNode, int targetNode, int letter)
{
	if (liste == NULL)
		return -1;

	while (liste->next != NULL)
		liste = liste->next;
	List element = malloc(sizeof(struct _list));
	if (element == NULL)
		return -1;
	element->startNode = startNode;
	element->targetNode = targetNode;
	element->letter = (unsigned char)letter;
	element->next = NULL;

	liste->next = element;
	return 0;
}

TrieH createTrieH(size_t maxNode)
{
	TrieH trieH = malloc(sizeof(struct _trieH));
	if (trieH == NULL)
		return NULL;
	trieH->maxNode = maxNode;
	trieH->nextNode = 1;
	trieH->transition = calloc(maxNode, sizeof(List));
	if (trieH->transition == NULL)
		return NULL;

	// Initialisation du vecteur de suppleants
	trieH->sup = malloc(maxNode * sizeof(int));
	if (trieH->sup == NULL)
		return NULL;
	for (size_t i = 0; i < maxNode; i++)
	{
		trieH->sup[i] = -1;
	}

	// Initialisation du vecteur d'états finaux
	trieH->finite = calloc(maxNode, sizeof(int));
	if (trieH->finite == NULL)
		return NULL;

	for (int i = 0; i < TAILLE_ALPHABET; ++i)
	{
		size_t hash = hashFunction(0, i, trieH->maxNode);
		if (trieH->transition[hash] == NULL)
			trieH->transition[hash] = createElement(0, 0, i);
		else
			insertLast(trieH->transition[hash], 0, 0, i);
	}

	return trieH;
}

int insertInTrieH(TrieH trieH, const char *word)
{
	int currentNode = 0;
	// vérifier si il n'existe pas encore de liste à la position retournée par la fonction de hachage
	if (trieH->nextNode + (int)strlen(word) <= (int)trieH->maxNode)
	{
		for (int i = 0; i < (int)strlen(word); i++)
		{
			int c = word[i] - DEBUT_ALPHABET;
			size_t hash = hashFunction(currentNode, c, trieH->maxNode);
			// Si la fonction de hachage nous renvoie un index sans liste
			if (trieH->transition[hash] == NULL)
			{
				trieH->transition[hash] = createElement(currentNode, trieH->nextNode, c);
				currentNode = trieH->nextNode;
				trieH->nextNode++;
			}
			else
			{
				List list = trieH->transition[hash];
				// Le hash existe deja, c-a-d il existe une liste chainée à cette position
				// Donc on doit parcourrir la liste chainée
				// Si on ne trouve pas de noeud ayant le meme noeud de départ et valeur, on l'ajoute en fin de liste
				while (list->letter != c)
				{
					// Arrivé en fin de liste sans trouver le bon elément, alors on l'ajoute
					if (list->next == NULL)
					{
						insertLast(list, currentNode, trieH->nextNode, c);
						trieH->nextNode++;
					}
					list = list->next;
				}
				// Cellule avec la bonne transition trouvée, vérifier si ce n'est pas
				// un état qui boucle sur lui même.
				if (list->startNode == 0 && list->targetNode == 0)
				{
					list->targetNode = trieH->nextNode;
					trieH->nextNode++;
				}
				currentNode = list->targetNode;
			}
		}
		trieH->finite[currentNode] = 1;
	}
	else
	{
		printf("Il n'y a plus assez de place pour insérer le mot \"%s\"\n", word);
	}
	return 0;
}

int createSupH(TrieH trieH)
{
	queue *q = createQueue(trieH->maxNode);
	if (q == NULL)
		return -1;

	// Boucle triviale (elements racine et elements de rang 1)
	for (int i = 0; i < TAILLE_ALPHABET; ++i)
	{
		if (getTargetNode(trieH, 0, i) != -1 && getTargetNode(trieH, 0, i) != 0)
		{
			trieH->sup[getTargetNode(trieH, 0, i)] = 0;
			pushQueue(q, getTargetNode(trieH, 0, i));
		}
	}

	// Seconde boucle
	while (sizeQueue(q))
	{
		int node = popQueue(q);
		for (int i = 0; i < TAILLE_ALPHABET; ++i)
		{
			if (getTargetNode(trieH, node, i) != -1)
			{
				int suppl = trieH->sup[node];
				while (getTargetNode(trieH, suppl, i) == -1)
				{
					suppl = trieH->sup[suppl];
				}
				suppl = getTargetNode(trieH, suppl, i);
				trieH->sup[getTargetNode(trieH, node, i)] = suppl;
				pushQueue(q, getTargetNode(trieH, node, i));
			}
		}
	}
	return 0;
}

size_t searchTextH(TrieH trieH, FILE *text)
{
	size_t cptMots = 0;
	int currentNode = 0;
	int character;
	while ((character = fgetc(text)) != EOF)
	{
		// Tant que le noeud n'a pas de transition avec le caractère courrant, on remonte
		// à son suppleant jusqu'a trouver un état qui a une transition avec ce caractère ou
		// arriver à l'état initial et dans e cas on aura forcémment une transition
		if (character < DEBUT_ALPHABET || character > FIN_ALPHABET)
			continue;
		character = character - DEBUT_ALPHABET;
		while (getTargetNode(trieH, currentNode, character) == -1)
		{
			currentNode = trieH->sup[currentNode];
			if (trieH->finite[currentNode] == 1)
				cptMots++;
		}
		currentNode = getTargetNode(trieH, currentNode, character);
		// On vérifie si une occurence n'a pas été trouvée
		// Vérification si l'état courrant est un état final, c.a-d, on a trouvé une
		// occurence de l'un des mots de l'ensemble dans le texte
		if (trieH->finite[currentNode] == 1)
			cptMots++;
	}
	return cptMots;
}

List createElement(int startNode, int targetNode, int letter)
{
	List list = malloc(sizeof(struct _list));
	if (list == NULL)
		return NULL;
	list->startNode = startNode;
	list->targetNode = targetNode;
	list->letter = (unsigned char)letter;
	list->next = NULL;

	return list;
}

int getTargetNode(TrieH trie, int startNode, int letter)
{
	List list = trie->transition[hashFunction(startNode, letter, trie->maxNode)];

	while (list != NULL)
	{
		if (letter == list->letter && startNode == list->startNode)
			return list->targetNode;
		list = list->next;
	}
	return -1;
}

size_t hashFunction(int currentNode, int letter, size_t maxNode)
{
	return (size_t)(21 * letter + currentNode) % maxNode;
}