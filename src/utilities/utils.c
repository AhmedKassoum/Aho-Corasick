#include <stdlib.h>
#include "utils.h"

// Strcuture de file utilisé pour le calcul des suppléants
struct queue {
	int *array;
	int size;
	int count;
	int front;
	int back;
};

queue *createQueue(size_t maxNode) {
	queue *q = malloc(sizeof(struct queue));
	if (q == NULL)
		return NULL;
	q->array = malloc(sizeof (int) * maxNode);
	if (q->array == NULL)
		return NULL;
	q->size = (int) maxNode;
	q->count = 0;
	q->front = 0;
	q->back = -1;
	return q;
}

void pushQueue(queue *q, int value) {
	if (q->back == q->size - 1)
		q->back = -1;
	q->array[++q->back] = value;
	q->count++;
}

int popQueue(queue *q) {
	int res = q->array[q->front++];
	if (q->front == q->size)
		q->front = 0;
	q->count--;
	return res;
}

int sizeQueue(queue *q) {
	return q->count;
}
