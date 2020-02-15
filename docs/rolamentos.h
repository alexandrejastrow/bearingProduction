#ifndef _ROLAMENTOS_H_
#define _ROLAMENTOS_H_

typedef struct rolamento ROLAMENTO;
typedef struct quantidadeDeRolamentos QTDROLAMENTOS;
typedef struct queue QUEUE;


void incrementCone(QTDROLAMENTOS *quantidadeFabricada);

void incrementCilindro(QTDROLAMENTOS *quantidadeFabricada);

void incrementEsferaAco(QTDROLAMENTOS *quantidadeFabricada);

void incrementEsferatitanio(QTDROLAMENTOS *quantidadeFabricada);

void incrementTimeCilindro(QTDROLAMENTOS *quantidadeFabricada, float tempo);

void incrementTimeCone(QTDROLAMENTOS *quantidadeFabricada, float tempo);

void incrementTimeEsferaAco(QTDROLAMENTOS *quantidadeFabricada, float tempo);

void incrementTimeEsferaTitanio(QTDROLAMENTOS *quantidadeFabricada, float tempo);

void geraMedia(QTDROLAMENTOS *quantidadeFabricada);


void printQuantidadeRolamentos(QTDROLAMENTOS *quantidadeFabricada);

void freeRolamentos(void *info);

void freeQuantidadeDeRolamentos(QTDROLAMENTOS *quantidadeFabricada);

ROLAMENTO *CreateRolamento(int priority, float tempoDeChegada);

int getPriorityRolamento(ROLAMENTO *rolamento);

QTDROLAMENTOS *createQtdRolamentos();

float startRolamento(float stop, QTDROLAMENTOS *quantidadeFabricada, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));

void printQuantidadeRolamentos(QTDROLAMENTOS *quantidadeFabricada);

#endif