#include <stdio.h>
#include "empresa.h"


int main(int argc, char **argv){
    if(argc > 1){

        double timeSimulation;
        sscanf(argv[1], "%lf", &timeSimulation);

        simulation(timeSimulation);

    }else{
        return 1;
    }
    return 0;
}