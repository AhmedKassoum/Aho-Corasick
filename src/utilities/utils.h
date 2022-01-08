#ifndef UTILS__H
#define UTILS__H

// Alphabet de '!' à '~' dans la table ASCII
#define DEBUT_ALPHABET    '!'
#define FIN_ALPHABET      '~'
#define TAILLE_ALPHABET 94

// Définition de la structure de file utilisé pour la construction
// des suppleants
typedef struct queue queue;

// création de la file
queue *createQueue(size_t maxNode);

// Insertion dans la file
void pushQueue(queue *q, int value);

// Déilefement d'un element de la file
int popQueue(queue *q);

// Fonction qui renvoi le nombre d'elements dans la file
int sizeQueue(queue *q);

#endif
