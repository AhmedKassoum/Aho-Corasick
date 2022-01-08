#ifndef ACH__H
#define ACH__H

#include <stdlib.h>

struct _list {
	int startNode, /* etat de depart de la transition */
    	targetNode; /* cible de la transition */
    unsigned char letter; /* etiquette de la transition */
    struct _list *next; /* maillon suivant */
};

typedef struct _list *List;

struct _trieH {
	size_t maxNode; /* Nombre maximal de noeuds du trie */
    int nextNode; /* Indice du prochain noeud disponible */
    List *transition; /* listes d’adjacence */
    char *finite; /* etats terminaux */
	int *sup;     // Tableau des supéants
};

typedef struct _trieH *TrieH;

// Fonction de hachage
size_t hashFunction(int currentNode, int letter, size_t maxNode);

// Fonction de création de la structure de table de hachage
TrieH createTrieH(size_t maxNode);

// Fonction d'insetion de mot dans la table de hachage.
int insertInTrieH(TrieH p, const char *word);

// Fonction de recherche dans un texte à l'aide du Trie construit
size_t searchTextH(TrieH p, FILE *text);

// Fonction de construction de la fonction suppléante.
int createSupH(TrieH p) ;

// Fonction permettant de créer un élement de la liste chainée
List createElement(int startNode, int targetNode, int letter);

// Fonction qui prend comme paramètre le trie, un noeud de début et la lettre de transition,
// elle retourne le noeud cible de la transition s'il existe, -1 sinon
int getTargetNode(TrieH  h, int startNode, int letter);

#endif
