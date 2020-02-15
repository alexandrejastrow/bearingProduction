#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "queue.h"
#include "rolamentos.h"

#define Chegada_Media_Cilindrico 21.5
#define Chegada_Media_Conico 19.1
#define Chegada_Media_Esferico 8.0

    enum priority {cilindrico = 1, conico, esferico};

float Gera_Exponencial(float avg){
    float u=0;
    do 
        u = ((float)rand()) / ((float) RAND_MAX);
    while ((u==0) || (u==1));
    return (-avg * log (u));
}


void simulation(double timeSimulation){

	srand(time(NULL));  
	/*inicio declaração de variaveis, listas, filas e estruturas*/
	double timeTotal = 0.0;
    float tempoChegadaCilindro = 0.0;
    float tempoChegadaCone = 0.0;
    float tempoChegadaEsfera = 0.0;
    float aux;

    QTDROLAMENTOS *quantidadeFabricada = createQtdRolamentos();

    QUEUE *tornoQueuePriority = createQueue();
    QUEUE *FresaQueuePriority = createQueue();
    QUEUE *MandrilQueuePriority = createQueue();
    /*fim declaração de variaveis, listas, filas e estruturas*/

    /*o quanto de tempo ficara nesse loop*/
    while(timeTotal < timeSimulation){

        /*gera a media que chega um rolamento de determinado tipo*/
        tempoChegadaCilindro = Gera_Exponencial(Chegada_Media_Cilindrico);
        tempoChegadaCone = Gera_Exponencial(Chegada_Media_Conico);
        tempoChegadaEsfera = Gera_Exponencial(Chegada_Media_Esferico);

        if(timeSimulation < tempoChegadaCilindro && timeSimulation < tempoChegadaCone && timeSimulation < tempoChegadaEsfera) break;

        ROLAMENTO *cilindro = CreateRolamento(cilindrico, tempoChegadaCilindro);
        ROLAMENTO *cone = CreateRolamento(conico, tempoChegadaCone);
        ROLAMENTO *esfera = CreateRolamento(esferico, tempoChegadaEsfera);
        /*inserindo os primeiros rolamenos nas "maquinas" a qual elas iniciam o processo*/
        insertQueue(tornoQueuePriority, cilindro, cilindrico);
        insertQueue(tornoQueuePriority, cone, conico);
        insertQueue(FresaQueuePriority, esfera, esferico);

        /*ficara nesse loop ate que os 3 rolamentos chegem de uma so vez, raro de acontecer*/
        while(tempoChegadaCilindro > 0 && tempoChegadaCone > 0 && tempoChegadaEsfera > 0){

            /*verifica qual sera o proximo rolamento a chegar*/
            if(tempoChegadaCilindro < tempoChegadaCone && tempoChegadaCilindro < tempoChegadaEsfera){
                
                /*enquanto nao chega mais rolamento estarta o processo de fabricacao*/
                aux = startRolamento(tempoChegadaCilindro, quantidadeFabricada, FresaQueuePriority, tornoQueuePriority, MandrilQueuePriority , insertQueue);
                /*adciona o tempo na maquina com o tempo total*/
                timeTotal += aux;
                /*caso chegue no tempo limite para o processo*/
                if(timeTotal >= timeSimulation) break;
                /*gera um novo tempo de chegada do rolamento*/
                tempoChegadaCilindro = Gera_Exponencial(Chegada_Media_Cilindrico);
                /*decrementa o valor que ficou na maquina dos demais rolamentos*/
                tempoChegadaCone -= aux;
                tempoChegadaEsfera -= aux;

                if(tempoChegadaCone <= 0){
                    tempoChegadaCone = Gera_Exponencial(Chegada_Media_Conico);
                    cone = CreateRolamento(conico, tempoChegadaCone);
                    insertQueue(tornoQueuePriority, cone, conico);
                }
                if(tempoChegadaEsfera <= 0){
                    tempoChegadaEsfera = Gera_Exponencial(Chegada_Media_Esferico);
                    esfera = CreateRolamento(esferico, tempoChegadaEsfera);
                    insertQueue(FresaQueuePriority, esfera, esferico);
                }
                /*cria um novo rolamento*/
                cilindro = CreateRolamento(cilindrico, tempoChegadaCilindro);
                /*insere na fila da maquina*/
                insertQueue(tornoQueuePriority, cilindro, cilindrico);

            }else if(tempoChegadaCone < tempoChegadaCilindro && tempoChegadaCone < tempoChegadaEsfera){

                /*enquanto nao chega mais rolamento estarta o processo de fabricacao*/
                aux = startRolamento(tempoChegadaCone, quantidadeFabricada, FresaQueuePriority, tornoQueuePriority, MandrilQueuePriority , insertQueue);
                /*adciona o tempo na maquina com o tempo total*/
                timeTotal += aux;
                /*caso chegue no tempo limite para o processo*/
                if(timeTotal >= timeSimulation) break;
                /*gera um novo tempo de chegada do rolamento*/
                tempoChegadaCone = Gera_Exponencial(Chegada_Media_Conico);
                /*decrementa o valor que ficou na maquina dos demais rolamentos*/
                tempoChegadaCilindro -= aux;
                tempoChegadaEsfera -= aux;

                if(tempoChegadaCilindro <= 0){
                    tempoChegadaCilindro = Gera_Exponencial(Chegada_Media_Cilindrico);
                     cilindro = CreateRolamento(cilindrico, tempoChegadaCilindro);
                    insertQueue(tornoQueuePriority, cilindro, cilindrico);
                }
                if(tempoChegadaEsfera <= 0){
                    tempoChegadaEsfera = Gera_Exponencial(Chegada_Media_Esferico);
                    esfera = CreateRolamento(esferico, tempoChegadaEsfera);
                    insertQueue(FresaQueuePriority, esfera, esferico);
                }
                /*cria um novo rolamento*/
                cone = CreateRolamento(conico, tempoChegadaCone);
                /*insere na fila da maquina*/
                insertQueue(tornoQueuePriority, cone, conico);


            }else{

                 /*enquanto nao chega mais rolamento estarta o processo de fabricacao*/
                aux = startRolamento(tempoChegadaEsfera, quantidadeFabricada, FresaQueuePriority, tornoQueuePriority, MandrilQueuePriority , insertQueue);
                /*adciona o tempo na maquina com o tempo total*/
                timeTotal += aux;
                /*caso chegue no tempo limite para o processo*/
                if(timeTotal >= timeSimulation) break;
                /*gera um novo tempo de chegada do rolamento*/
                tempoChegadaEsfera = Gera_Exponencial(Chegada_Media_Esferico);
                /*decrementa o valor que ficou na maquina dos demais rolamentos*/
                tempoChegadaCilindro -= aux;
                tempoChegadaCone -= aux;

                if(tempoChegadaCilindro <= 0){
                    tempoChegadaCilindro = Gera_Exponencial(Chegada_Media_Cilindrico);
                     cilindro = CreateRolamento(cilindrico, tempoChegadaCilindro);
                    insertQueue(tornoQueuePriority, cilindro, cilindrico);
                }
                if(tempoChegadaCone <= 0){
                    tempoChegadaCone = Gera_Exponencial(Chegada_Media_Conico);
                    cone = CreateRolamento(conico, tempoChegadaCone);
                    insertQueue(tornoQueuePriority, cone, conico);
                }
                /*cria um novo rolamento*/
                esfera = CreateRolamento(esferico, tempoChegadaEsfera);
                insertQueue(FresaQueuePriority, esfera, esferico);

                
            }
        }
    }
    /*funcao que gera o tempo medio dividindo a quantidade de rolamentos pelo tempo total*/
    geraMedia(quantidadeFabricada);
    /*funcao que imprime na tela a quantidade de rolamentos e seu tempo medio*/
    printQuantidadeRolamentos(quantidadeFabricada);
    /*funcoes que liberam as memorias alocadas*/
    freeQueue(tornoQueuePriority, freeRolamentos);
    freeQueue(MandrilQueuePriority, freeRolamentos);
    freeQueue(FresaQueuePriority, freeRolamentos);
    freeQuantidadeDeRolamentos(quantidadeFabricada);



}
   