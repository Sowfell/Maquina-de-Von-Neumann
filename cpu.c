#include <stdlib.h>
#include "cpu.h"
#include "memoria.h"

CPU* iniciar_cpu(){
    CPU *cpu = (CPU*)malloc(sizeof(cpu));
    if(cpu != NULL){
        cpu->pc = 0;
    }
    return cpu;
}

void iniciar_programa(CPU* cpu,Memoria* ram){

}

void buscar_instrucao(CPU* cpu,Memoria* ram){
    cpu->mar = cpu->pc;
    cpu->mbr = memoria[mar];

}

void ler_instrucao(CPU* cpu){

    cpu->ir = cpu->mbr >> 19;

}
void executar_instrucao(CPU* cpu){

}



