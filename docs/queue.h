#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_


typedef struct queue QUEUE;

QUEUE *createQueue();

void insertQueue(QUEUE *queue, void *data, int priority);

void *getDataQueue(QUEUE *queue);

void imprime(QUEUE *queue, void (*imp)(void*));

void printQueue(QUEUE *queue, void (*printQueueInfo)(void*));

void freeQueue(QUEUE *queue, void (*freeInfo)(void*));

int getLenQueue(QUEUE *queue);

#endif