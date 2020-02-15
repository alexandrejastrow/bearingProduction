#include <stdlib.h>
#include <stdlib.h>
#include "rolamentos.h"
#include "queue.h"

typedef void (*genericFunc)();

struct nodo{
	genericFunc func;
	struct nodo *next;
};

struct list{
	int size;
	struct nodo *head;
};

typedef struct nodo NODO;
typedef struct list LIST;



void setHeadList(LIST *list, NODO *nodo);
NODO *getHeadList(LIST *list);
void setDataList(NODO *nodo, genericFunc func);
genericFunc getDataList(NODO *nodo);
void setNextNodoList(NODO *current, NODO *next);
NODO *getNextNodoList(NODO *current);
void freeNodoList(NODO *nodo);
void incrementList(LIST *list);
void decrementList(LIST *list);
void setSizeList(LIST* list, int size);
int getSizeList(LIST *list);
genericFunc getListFunc(LIST *list);

int getSizeList(LIST *list){
	return list->size;
}
NODO *createNodoList(genericFunc func){

	NODO *new = (NODO*)malloc(sizeof(NODO));

	if(!new) return NULL;

	setDataList(new, func);
	setNextNodoList(new, NULL);

	return new;
}

LIST *createList(){

	LIST *new = (LIST*)malloc(sizeof(LIST));

	if(!new) return NULL;

	setHeadList(new, NULL);
	setSizeList(new, 0);

	return new;
}

genericFunc getListData(LIST *list){
	genericFunc func = NULL;
	if(getHeadList(list)){
		NODO *temporary = getHeadList(list);
		NODO *current = getNextNodoList(temporary);
		func = getDataList(temporary);
		setHeadList(list, current);
		freeNodoList(temporary);
		decrementList(list);
		return func;
	}
	return NULL;
}


void insertList(LIST *list, genericFunc func){

	NODO *new = createNodoList(func);

	if(!new) return;

	if(getHeadList(list)){

		NODO *temporary = getHeadList(list);

		while(getNextNodoList(temporary)){
			temporary = getNextNodoList(temporary);
		}
		setNextNodoList(temporary, new);

	}else{
		setHeadList(list, new);
	}

	incrementList(list);
}

void freeList(LIST *list){

	NODO *temporary = getHeadList(list);
	NODO *previous = NULL;


	while(temporary){
		previous = temporary;
		temporary = getNextNodoList(temporary);
		free(previous);
	}
	free(list);
}
void incrementList(LIST* list){
	list->size++;
}

void decrementList(LIST* list){
	list->size--;
}

void setSizeList(LIST* list, int size){
	list->size = size;
}

void setHeadList(LIST *list, NODO *nodo){
	list->head = nodo;
}

NODO *getHeadList(LIST *list){
	if(list){
		return list->head;
	}
	return NULL;
}

void setDataList(NODO *nodo, genericFunc func){
	nodo->func = func;
}

genericFunc getDataList(NODO *nodo){

	if(nodo){
		return nodo->func;
	}
	return NULL;

}

void setNextNodoList(NODO *current, NODO *next){
	current->next = next;
}

NODO *getNextNodoList(NODO *current){
	if(current){
		return current->next;
	}
	return NULL;
}

void freeNodoList(NODO *nodo){
	free(nodo);
}

/*******************************************************************/

