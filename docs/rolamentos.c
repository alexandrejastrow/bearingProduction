#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "queue.h"

/*define da estadia nos equipamentos por cada rolamento*/
#define Estadia_Mandril_Cilindrico 1.2
#define Estadia_Fresa_Cilindrico 0.5
#define Estadia_Torno_Cilindrico 0.8
#define Estadia_Mandril_Conico 2.1
#define Estadia_Torno_Conico 1.8
#define Estadia_Mandril_Esferico_Aco 1.4
#define Estadia_Fresa_Esferico_Aco 0.5
#define Estadia_Torno_Esferico_Aco 1.0
#define Estadia_Mandril_Esferico_Titanio 1.5
#define Estadia_Fresa_Esferico_Titanio 0.6
#define Estadia_Torno_Esferico_Titanio 1.6

/*define para ajudar a leitura do codigo*/
#define ProximoTornoCilindrico 3
#define ProximoTornoConico 1
#define ProximoFresaEsfericoTitanio 4
#define ProximotornoEsfericoTitanio 2

/*tipo do rolamento*/
#define aco 26
#define titanio 22
	
	/*prioridade dos rolamentos*/
	enum priority {cilindrico = 1, conico, esferico};

/*struct de rolamento generico*/
struct rolamento{
	float tempo;
	LIST *productionOrder;

};
/*struct que contabiliza quantidade e tempo medio dos rolamentos*/
struct quantidadeDeRolamentos{

    int quantidadeFabricadaCilindro, quantidadeFabricadaCone, quantidadeFabricadaEsferaAco, quantidadeFabricadaEsferatitanio;
    float timeCilindro, timeCone, timeEsferaAco, timeEsferatitanio;

};

typedef struct rolamento ROLAMENTO;
typedef struct quantidadeDeRolamentos QTDROLAMENTOS;
typedef float (*FUNC)(QTDROLAMENTOS *, ROLAMENTO *, QUEUE *, QUEUE *, QUEUE * , void (*nextMachine)(QUEUE*, void*, int));
typedef void (*genericFunc)();

/*declarando as funçoes basicas*/
float tempo(float Estadia_Equipamento_Rolamento);
void setTimeRolamento(ROLAMENTO *rolamento, float tempo);
float getTimeRolamento(ROLAMENTO *rolamento);
void setProductionOrder(ROLAMENTO *rolamento, LIST *list);
LIST *getProductionOrder(ROLAMENTO *rolamento);
float mandrilCilindrico(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float fresaCilindrico(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float tornoCilindrico(QTDROLAMENTOS *quantidadeFabricada, ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float mandrilConico(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float tornoConico(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float mandrilEsfericoAco(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float fresaEsfericoAco(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float tornoEsfericoAco(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float mandrilEsfericoTitanio(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float fresaEsfericoTitanio(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
float tornoEsfericoTitanio(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int));
void incrementCone(QTDROLAMENTOS *quantidadeFabricada);
void incrementCilindro(QTDROLAMENTOS *quantidadeFabricada);
void incrementEsferaAco(QTDROLAMENTOS *quantidadeFabricada);
void incrementEsferatitanio(QTDROLAMENTOS *quantidadeFabricada);
void incrementTimeCilindro(QTDROLAMENTOS *quantidadeFabricada, float tempo);
void incrementTimeCone(QTDROLAMENTOS *quantidadeFabricada, float tempo);
void incrementTimeEsferaAco(QTDROLAMENTOS *quantidadeFabricada, float tempo);
void incrementTimeEsferaTitanio(QTDROLAMENTOS *quantidadeFabricada, float tempo);
int getQuantidadeCone(QTDROLAMENTOS *quantidadeFabricada);
int getQuantidadeCilindro(QTDROLAMENTOS *quantidadeFabricada);
int getQuantidadeEsferaAco(QTDROLAMENTOS *quantidadeFabricada);
int getQuantidadeEsferatitanio(QTDROLAMENTOS *quantidadeFabricada);
void setQuantidadeCone(QTDROLAMENTOS *quantidadeFabricada, int valor);
void setQuantidadeCilindro(QTDROLAMENTOS *quantidadeFabricada, int valor);
void setQuantidadeEsferaAco(QTDROLAMENTOS *quantidadeFabricada, int valor);
void setQuantidadeEsferatitanio(QTDROLAMENTOS *quantidadeFabricada, int valor);
void setTimeCilindro(QTDROLAMENTOS *quantidadeFabricada, float tempo);
void setTimeCone(QTDROLAMENTOS *quantidadeFabricada, float tempo);
void setTimeEsferaAco(QTDROLAMENTOS *quantidadeFabricada, float tempo);
void setTimeEsferaTitanio(QTDROLAMENTOS *quantidadeFabricada, float tempo);
float getTimeCilindro(QTDROLAMENTOS *quantidadeFabricada);
float getTimeCone(QTDROLAMENTOS *quantidadeFabricada);
float getTimeEsferaAco(QTDROLAMENTOS *quantidadeFabricada);
float getTimeEsferaTitanio(QTDROLAMENTOS *quantidadeFabricada);
void geraMedia(QTDROLAMENTOS *quantidadeFabricada);
void printQuantidadeRolamentos(QTDROLAMENTOS *quantidadeFabricada);
void freeRolamentos(void *info);
void freeRolamento(ROLAMENTO *rolamento);
void freeQuantidadeDeRolamentos(QTDROLAMENTOS *quantidadeFabricada);


/*funcao que cria o rolamento recebendo sua prioridade que inplicitamente informa seu tipo*/
ROLAMENTO *CreateRolamento(int priority, float tempoDeChegada){


	ROLAMENTO *new = (ROLAMENTO*)malloc(sizeof(ROLAMENTO));
	if(!new) return NULL;

	/*cria uma lista para armazenar os ponteiros para funcao, ate o momento nao sei como fazer o cast de VOID* para *daFuncao */
	LIST *list = createList();
	if(!list){
		free(new);
		return NULL;
	}

	setTimeRolamento(new, tempoDeChegada);
	/*verifica qual o rolamento*/
	if(priority == cilindrico){
		/*insere na lista as funcoes que executara o processamento do rolamento*/
		insertList(list,  (genericFunc)tornoCilindrico);
		insertList(list,  (genericFunc)fresaCilindrico);
		insertList(list,  (genericFunc)tornoCilindrico);
		insertList(list,  (genericFunc)mandrilCilindrico);

	}else if(priority == conico){

		/*insere na lista as funcoes que executara o processamento do rolamento*/
		insertList(list,  (genericFunc)tornoConico);
		insertList(list,  (genericFunc)mandrilConico);
		insertList(list,  (genericFunc)tornoConico);

	}else if(priority == esferico){

		/*gera um numero random de 0 a 99*/
		int random = rand()%99;

		if(random >= 9){
			/*insere na lista as funcoes que executara o processamento do rolamento*/
			insertList(list, (genericFunc)fresaEsfericoAco);
			insertList(list, (genericFunc)mandrilEsfericoAco);
			insertList(list, (genericFunc)tornoEsfericoAco);

		}else{

			/*insere na lista as funcoes que executara o processamento do rolamento*/
			insertList(list, (genericFunc)fresaEsfericoTitanio);
			insertList(list, (genericFunc)mandrilEsfericoTitanio);
			insertList(list, (genericFunc)tornoEsfericoTitanio);
			insertList(list, (genericFunc)fresaEsfericoTitanio);
			insertList(list, (genericFunc)tornoEsfericoTitanio);
		}
		
	}else{
		/*caso onde a prioridade nao esta de acordo*/
		free(new);
		return NULL;
	}
	/*seta o ponteiro para lista da struct com a lista criada anteriormente*/
	setProductionOrder(new, list);
	
	return new;
}

QTDROLAMENTOS *createQtdRolamentos(){


	QTDROLAMENTOS *quantidadeFabricada = (QTDROLAMENTOS*)malloc(sizeof(QTDROLAMENTOS));

	if(!quantidadeFabricada) return NULL;
	/*cria e seta todas as informaçoes da struct para 0*/
	setQuantidadeCilindro(quantidadeFabricada, 0);
	setQuantidadeCone(quantidadeFabricada, 0);
	setQuantidadeEsferaAco(quantidadeFabricada, 0);
	setQuantidadeEsferatitanio(quantidadeFabricada, 0);
	setTimeCilindro(quantidadeFabricada, 0.0);
	setTimeCone(quantidadeFabricada, 0.0);
	setTimeEsferaAco(quantidadeFabricada, 0.0);
	setTimeEsferaTitanio(quantidadeFabricada, 0.0);

	return quantidadeFabricada;
}

float startRolamento(float stop, QTDROLAMENTOS *quantidadeFabricada, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){

	/*declarando funcoes*/
	float timeTotal = 0.0; 
	float tempoNaMaquina = 0.0;
	FUNC funcMachine;
	ROLAMENTO *rolamento = NULL;

	/*loop ate o timeTotal ser igual ao tempo que a fucao tem para ser executada ou ate as maquinas nao terem mais rolamentos*/
	while(timeTotal < stop){
		

		/*processo do torno, se nao estiver vazio*/
		if(getLenQueue(torno)){
			/*pega o primeiro rolamento da fila*/
			rolamento = getDataQueue(torno);
			/*pega a primeira funcao da lista de funcoes*/
			funcMachine = (FUNC)getListData(getProductionOrder(rolamento));
			/*executa essa funcao e retorna um valor que sera acrecentado ao valor total*/
			tempoNaMaquina = funcMachine(quantidadeFabricada, rolamento, fresa, torno, mandril, nextMachine);
			timeTotal += tempoNaMaquina;
		}

		/*virifica se o tempo de execucao se esgotou*/
		if(timeTotal >= stop) return timeTotal;
		/**/

		/*processo do mandril, se nao estiver vazio*/
		if(getLenQueue(mandril)){
			/*pega o primeiro rolamento da fila*/
			rolamento = getDataQueue(mandril);
			/*pega a primeira funcao da lista de funcoes*/
			funcMachine = (FUNC)getListData(getProductionOrder(rolamento));
			/*executa essa funcao e retorna um valor que sera acrecentado ao valor total*/
			tempoNaMaquina = funcMachine(quantidadeFabricada, rolamento, fresa, torno, mandril, nextMachine);
			timeTotal += tempoNaMaquina;

		}
		/*virifica se o tempo de execucao se esgotou*/
		if(timeTotal >= stop) return timeTotal;

		/*processo da fresa, se nao estiver vazio*/
		if(getLenQueue(fresa)){
			/*pega o primeiro rolamento da fila*/
			rolamento = getDataQueue(fresa);
			/*pega a primeira funcao da lista de funcoes*/
			funcMachine = (FUNC)getListData(getProductionOrder(rolamento));
			/*executa essa funcao e retorna um valor que sera acrecentado ao valor total*/
			tempoNaMaquina = funcMachine(quantidadeFabricada,rolamento, fresa, torno, mandril, nextMachine);
			timeTotal += tempoNaMaquina;

		}

		/*se as maquinas estiverem vazias retorna o tempo stop, que e o tempo que ira demorar para a chegada do proximo rolamento*/
		if(!getLenQueue(fresa) && !getLenQueue(fresa) && !getLenQueue(fresa)) return stop;
	}

	return timeTotal;

}

float tempo(float Estadia_Equipamento_Rolamento){

    float u = ((float)rand()) / ((float) RAND_MAX);
    return 2.0 * Estadia_Equipamento_Rolamento * u;
}



void setProductionOrder(ROLAMENTO *rolamento, LIST *list){
	rolamento->productionOrder = list;
}


LIST *getProductionOrder(ROLAMENTO *rolamento){
	return rolamento->productionOrder;
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float mandrilCilindrico(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	incrementCilindro(quantidadeFabricada);
	incrementTimeCilindro(quantidadeFabricada, getTimeRolamento(rolamentoProcessando));
	freeRolamento(rolamentoProcessando);

	return tempo(Estadia_Mandril_Cilindrico);
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float fresaCilindrico(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	nextMachine(torno, rolamentoProcessando, cilindrico);

	return tempo(Estadia_Fresa_Cilindrico);
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float tornoCilindrico(QTDROLAMENTOS *quantidadeFabricada, ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	if(getSizeList(getProductionOrder(rolamentoProcessando)) == ProximoTornoCilindrico){

		nextMachine(fresa, rolamentoProcessando, cilindrico);
	}else{
		nextMachine(mandril, rolamentoProcessando, cilindrico);
	}

	return tempo(Estadia_Torno_Cilindrico);
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float mandrilConico(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	nextMachine(torno, rolamentoProcessando, conico);
	
	return tempo(Estadia_Mandril_Conico);
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float tornoConico(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	if(getSizeList(getProductionOrder(rolamentoProcessando)) == ProximoTornoConico){

		nextMachine(mandril, rolamentoProcessando, conico);
	}else{
		incrementTimeCone(quantidadeFabricada, getTimeRolamento(rolamentoProcessando));
		incrementCone(quantidadeFabricada);
		freeRolamento(rolamentoProcessando);
	}

	return tempo(Estadia_Torno_Conico);
}
/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float mandrilEsfericoAco(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	nextMachine(torno, rolamentoProcessando, esferico);

	return tempo(Estadia_Mandril_Esferico_Aco);
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float fresaEsfericoAco(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	nextMachine(mandril, rolamentoProcessando, esferico);

	return tempo(Estadia_Fresa_Esferico_Aco);
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float tornoEsfericoAco(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	incrementTimeEsferaAco(quantidadeFabricada, getTimeRolamento(rolamentoProcessando));
	incrementEsferaAco(quantidadeFabricada);
	freeRolamento(rolamentoProcessando);

	return tempo(Estadia_Torno_Esferico_Aco);
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float mandrilEsfericoTitanio(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	nextMachine(torno, rolamentoProcessando, esferico);

	return tempo(Estadia_Mandril_Esferico_Titanio);
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float fresaEsfericoTitanio(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	if(getSizeList(getProductionOrder(rolamentoProcessando)) == ProximoFresaEsfericoTitanio){

		nextMachine(mandril, rolamentoProcessando, esferico);
	}else{
		nextMachine(torno, rolamentoProcessando, esferico);
	}

	return tempo(Estadia_Fresa_Esferico_Titanio);
}

/*recebe os parametros se for a ultima maquina do rolamento ela incrementa no total e libera a memoria, se o rolamento passar por ela varias vezes, verifica qual o processo deve ser feito,
caso nao for a ultima maquina eh encaminhado para a seguinte*/
float tornoEsfericoTitanio(QTDROLAMENTOS *quantidadeFabricada,ROLAMENTO *rolamentoProcessando, QUEUE *fresa, QUEUE *torno, QUEUE *mandril, void (*nextMachine)(QUEUE*, void*, int)){
	
	if(getSizeList(getProductionOrder(rolamentoProcessando)) == ProximotornoEsfericoTitanio){

		nextMachine(fresa, rolamentoProcessando, esferico);
	}else{
		incrementTimeEsferaTitanio(quantidadeFabricada, getTimeRolamento(rolamentoProcessando));
		incrementEsferatitanio(quantidadeFabricada);
		freeRolamento(rolamentoProcessando);
	}

	return tempo(Estadia_Torno_Esferico_Titanio);
}

void incrementCone(QTDROLAMENTOS *quantidadeFabricada){
	quantidadeFabricada->quantidadeFabricadaCone++;

}

void incrementCilindro(QTDROLAMENTOS *quantidadeFabricada){
	quantidadeFabricada->quantidadeFabricadaCilindro++;
}

void incrementEsferaAco(QTDROLAMENTOS *quantidadeFabricada){
	quantidadeFabricada->quantidadeFabricadaEsferaAco++;
}

void incrementEsferatitanio(QTDROLAMENTOS *quantidadeFabricada){
	quantidadeFabricada->quantidadeFabricadaEsferatitanio++;
}

void incrementTimeCilindro(QTDROLAMENTOS *quantidadeFabricada, float tempo){
	quantidadeFabricada->timeCilindro += tempo;
}

void incrementTimeCone(QTDROLAMENTOS *quantidadeFabricada, float tempo){
	quantidadeFabricada->timeCone += tempo;
}

void incrementTimeEsferaAco(QTDROLAMENTOS *quantidadeFabricada, float tempo){
	quantidadeFabricada->timeEsferaAco += tempo;
}

void incrementTimeEsferaTitanio(QTDROLAMENTOS *quantidadeFabricada, float tempo){
	quantidadeFabricada->timeEsferatitanio += tempo;
}
/**/
int getQuantidadeCone(QTDROLAMENTOS *quantidadeFabricada){
	return quantidadeFabricada->quantidadeFabricadaCone;

}

int getQuantidadeCilindro(QTDROLAMENTOS *quantidadeFabricada){
	return quantidadeFabricada->quantidadeFabricadaCilindro;
}

int getQuantidadeEsferaAco(QTDROLAMENTOS *quantidadeFabricada){
	return quantidadeFabricada->quantidadeFabricadaEsferaAco;
}

int getQuantidadeEsferatitanio(QTDROLAMENTOS *quantidadeFabricada){
	return quantidadeFabricada->quantidadeFabricadaEsferatitanio;
}
/**/
void setQuantidadeCone(QTDROLAMENTOS *quantidadeFabricada, int valor){
	quantidadeFabricada->quantidadeFabricadaCone = valor;

}

void setQuantidadeCilindro(QTDROLAMENTOS *quantidadeFabricada, int valor){
	quantidadeFabricada->quantidadeFabricadaCilindro = valor;
}

void setQuantidadeEsferaAco(QTDROLAMENTOS *quantidadeFabricada, int valor){
	quantidadeFabricada->quantidadeFabricadaEsferaAco = valor;
}

void setQuantidadeEsferatitanio(QTDROLAMENTOS *quantidadeFabricada, int valor){
	quantidadeFabricada->quantidadeFabricadaEsferatitanio = valor;
}
/**/
void setTimeCilindro(QTDROLAMENTOS *quantidadeFabricada, float tempo){
	quantidadeFabricada->timeCilindro = tempo;
}

void setTimeCone(QTDROLAMENTOS *quantidadeFabricada, float tempo){
	quantidadeFabricada->timeCone = tempo;
}

void setTimeEsferaAco(QTDROLAMENTOS *quantidadeFabricada, float tempo){
	quantidadeFabricada->timeEsferaAco = tempo;
}

void setTimeEsferaTitanio(QTDROLAMENTOS *quantidadeFabricada, float tempo){
	quantidadeFabricada->timeEsferatitanio = tempo;
}
/**/
float getTimeCilindro(QTDROLAMENTOS *quantidadeFabricada){
	return quantidadeFabricada->timeCilindro;
}

float getTimeCone(QTDROLAMENTOS *quantidadeFabricada){
	return quantidadeFabricada->timeCone;
}

float getTimeEsferaAco(QTDROLAMENTOS *quantidadeFabricada){

	return quantidadeFabricada->timeEsferaAco;
}

float getTimeEsferaTitanio(QTDROLAMENTOS *quantidadeFabricada){
	return quantidadeFabricada->timeEsferatitanio;
}

/*funcao que gera a media de chegada do rolamento no tempo estipulado de execucao*/
void geraMedia(QTDROLAMENTOS *quantidadeFabricada){

	if(getQuantidadeCilindro(quantidadeFabricada)){
		quantidadeFabricada->timeCilindro /= getQuantidadeCilindro(quantidadeFabricada);
	}else{
		quantidadeFabricada->timeCilindro = 0.0;
	}
	if(getQuantidadeCone(quantidadeFabricada)){
		quantidadeFabricada->timeCone /= getQuantidadeCone(quantidadeFabricada);
	}else{
		quantidadeFabricada->timeCone = 0.0;
	}

	if(getQuantidadeEsferaAco(quantidadeFabricada)){
		/*soma o tempo total de chegada das esfera de aco e titanio, e depois tira a media de chegada de cada tipo (na execução pode ser diferente, depende da sorte)*/
		float tempoTotalEsfera = (getTimeEsferaAco(quantidadeFabricada)+getTimeEsferaTitanio(quantidadeFabricada));
		quantidadeFabricada->timeEsferaAco = tempoTotalEsfera/getQuantidadeEsferaAco(quantidadeFabricada);

		if(getQuantidadeEsferatitanio(quantidadeFabricada)){
			quantidadeFabricada->timeEsferatitanio = tempoTotalEsfera/getQuantidadeEsferatitanio(quantidadeFabricada);
		}else{
			quantidadeFabricada->timeEsferatitanio = 0.0;
		}

	}else{
		quantidadeFabricada->timeEsferaAco = 0.0;
	}

}
/*funcao que printa a struct QTDROLAMENTOS*/
void printQuantidadeRolamentos(QTDROLAMENTOS *quantidadeFabricada){

	printf("Cilindros  : %7.2f \t %d \n",getTimeCilindro(quantidadeFabricada), getQuantidadeCilindro(quantidadeFabricada));
	printf("Conicos    : %7.2f \t %d \n",getTimeCone(quantidadeFabricada), getQuantidadeCone(quantidadeFabricada));
	printf("Aco        : %7.2f \t %d \n",getTimeEsferaAco(quantidadeFabricada), getQuantidadeEsferaAco(quantidadeFabricada));
	printf("Titanio    : %7.2f \t %d \n",getTimeEsferaTitanio(quantidadeFabricada), getQuantidadeEsferatitanio(quantidadeFabricada));
	
}
/*funcao que e passada como parametro para liberar o rolamento de uma fila, lista, pilha e etc*/
void freeRolamentos(void *info){

	ROLAMENTO *rolamento = (ROLAMENTO*)info;

	freeList(getProductionOrder(rolamento));
	free(rolamento);
}
/*funcao interna para liberar espaco de memoria*/
void freeRolamento(ROLAMENTO *rolamento){
	freeList(getProductionOrder(rolamento));
	free(rolamento);
}
/*funcao para liberar a struct QTDROLAMENTOS*/
void freeQuantidadeDeRolamentos(QTDROLAMENTOS *quantidadeFabricada){
	free(quantidadeFabricada);
}
void setTimeRolamento(ROLAMENTO *rolamento, float tempo){
	rolamento->tempo = tempo;
}
float getTimeRolamento(ROLAMENTO *rolamento){
	return rolamento->tempo;
}