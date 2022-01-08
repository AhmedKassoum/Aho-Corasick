#ifndef ACM__H
#define ACM__H

#include <stdlib.h>

struct _trie {
    size_t maxNode; /* Nombre maximal de noeuds du trie */
    int nextNode; /* Indice du prochain noeud disponible */
    int **transition; /* matrice de transition */
    char *finite; /* vecteur des états finaux */
	int *sup; /* vecteur des suppleants */
};

typedef struct _trie *TrieM;

// Fonction de création de la structure de matrice de transition
TrieM createTrieM(size_t maxNode);

// Fonction d'insertion d'un mot dans la matrice de transition
int insertInTrieM(TrieM p, const char *word);

// Procédure de construction de la fonction suppléante
int createSupM(TrieM p) ;

// Fonction de recherche dans un texte via le dictionnaire construit
// dans la matrice de transition
size_t searchTextM(TrieM p, FILE *text);


#endif
