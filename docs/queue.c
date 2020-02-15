#include <stdlib.h>
#include <stdio.h>
struct nodo{
	void *data;
	int priority;
	struct nodo *next;
};

struct queue{
	int lenQueue;
	struct nodo *head;
};

typedef struct nodo NODO;
typedef struct queue QUEUE;

void setHead(QUEUE *queue, NODO *nodo);
NODO *getHead(QUEUE *queue);
void setData(NODO *nodo, void *data);
void *getData(NODO *nodo);
void setPriority(NODO *nodo, int priority);
int getPriority(NODO *nodo);
void setNextNodo(NODO *current, NODO *next);
NODO *getNextNodo(NODO *current);
void freeNodo(NODO *nodo);
void setLenQueue(QUEUE *queue);
int getLenQueue(QUEUE *queue);
void incrementQueue(QUEUE *queue);
void decrementQueue(QUEUE *queue);

NODO *createNodo(int priority, void *data){

	NODO *new = (NODO*)malloc(sizeof(NODO));

	if(!new) return NULL;

	setData(new, data);
	setPriority(new, priority);
	setNextNodo(new, NULL);

	return new;
}

QUEUE *createQueue(){

	QUEUE *new = (QUEUE*)malloc(sizeof(QUEUE));

	if(!new) return NULL;

	setHead(new, NULL);
	setLenQueue(new);

	return new;
}

void *getDataQueue(QUEUE *queue){
	if(getHead(queue)){
		NODO *temporary = getHead(queue);
		NODO *current = getNextNodo(temporary);
		void *data = getData(temporary);
		setHead(queue, current);
		freeNodo(temporary);
		decrementQueue(queue);
		return data;
	}
	return NULL;
}

void insertQueue(QUEUE *queue, void *data, int priority){

	NODO *new = createNodo(priority, data);
	if(new){
		NODO *current = getHead(queue);
		incrementQueue(queue);
		if(!current){
			setHead(queue, new);
		}else{
			NODO *temporary = NULL;

			while(current){

				if(priority > getPriority(current)){
					if(!temporary){
						setHead(queue, new);			
						setNextNodo(new, current);
						return;
					}else{
						setNextNodo(temporary, new);
						setNextNodo(new, current);
						return;
					}
				}
				temporary = current;
				current = getNextNodo(current);
			}
			setNextNodo(temporary, new);
		}
	}
}

void freeQueue(QUEUE *queue, void (*freeInfo)(void*)){

	NODO *temporary = getHead(queue);
	NODO *previous = NULL;

	while(temporary){
		previous = temporary;
		temporary = getNextNodo(temporary);
		freeInfo(getData(previous));
		free(previous);
	}
	free(queue);
}

void setHead(QUEUE *queue, NODO *nodo){
	queue->head = nodo;
}

NODO *getHead(QUEUE *queue){
	if(queue){
		return queue->head;
	}
	return NULL;
}

void setData(NODO *nodo, void *data){
	nodo->data = data;
}

void *getData(NODO *nodo){
	return nodo->data;
}

void setPriority(NODO *nodo, int priority){

	nodo->priority = priority;
}

int getPriority(NODO *nodo){
	if(nodo){
		return nodo->priority;
	}
	return -1;
}

void setNextNodo(NODO *current, NODO *next){
	current->next = next;
}

NODO *getNextNodo(NODO *current){
	if(current){
		return current->next;
	}
	return NULL;
}

void freeNodo(NODO *nodo){
	free(nodo);
}

void setLenQueue(QUEUE *queue){
	queue->lenQueue = 0;
}
int getLenQueue(QUEUE *queue){
	return queue->lenQueue;
}

void incrementQueue(QUEUE *queue){
	queue->lenQueue++;
}
void decrementQueue(QUEUE *queue){
	queue->lenQueue--;
}
void printQueue(QUEUE *queue, void (*printQueueInfo)(void*)){

	if(queue){

		NODO *temporary;

		for(temporary = getHead(queue); temporary != NULL; temporary = getNextNodo(temporary)){
			printQueueInfo(getData(temporary));
		}
	}
}
