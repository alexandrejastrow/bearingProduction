#ifndef _LIST_H_
#define _LIST_H_

typedef struct list LIST;
typedef void (*genericFunc)();

LIST *createList();

genericFunc getListData(LIST *list);

void insertList(LIST *list, genericFunc func);

void insertFuncList(LIST *list, genericFunc);

void freeList(LIST *list);

int getSizeList(LIST *list);

#endif