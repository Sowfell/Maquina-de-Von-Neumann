#include <stdlib.h>
#include "cpu.h"
#include "memoria.h"

//Esse é um vetor que serve para indicar quantos bytes são necessários buscar
//da memória de acordo com cada instrução, cada posição do vetor equivale à uma
//instrução do conjunto completo, de modo que já estão na ordem correta. Ou seja, por exemplo
//hlt que tem opcode 0b00000 equivale a posição 1, nop que tem 0b00001 está na posição 2, e assim por diante

unsigned char tamanho_opcodes[30] = {1,1, //hlt .. nop
                                     2,2,2,2,2,2,2,2,2,2,2, //ldr ... xor
                                     1, // not
                                     3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} //je .. rsh

CPU* iniciar_cpu(){
    CPU *cpu = (CPU*)malloc(sizeof(cpu));
    if(cpu != NULL){
        cpu->pc = 0;
    }
    return cpu;
}

void iniciar_programa(CPU* cpu,Memoria* ram){

    unsigned char t_instrucao = 0;

    t_instrucao = buscar_instrucao(cpu,ram);
    decodificar_instrucao(cpu, t_instrucao);
    executar_instrucao(cpu,ram);

}

unsigned char buscar_instrucao(CPU* cpu,Memoria* ram){ //A busca também faz uma pré-decodificação
    if(cpu == NULL || ram == NULL)              //que apenas analisa quantos bytes ainda devem ser buscados
        return 0;
    cpu->mar = cpu->pc;
    cpu->mbr = ram->endereco[cpu->mar]; //Pega o Opcode da instrução
    cpu->ir = cpu->mbr >> 3;

    //Não é preciso verificar se a instrução tem somente 1 byte, se esse for o caso
    //a busca já está completa
    if(tamanho_opcodes[cpu->ir] < 1 || tamanho_opcodes[cpu->ir] > 3)
        perror("Erro de codificação de instrução, opcode inválido");
        return; //Só uma verificação de segurança

    cpu->pc++;
    if(tamanho_opcodes[cpu->ir] >= 2){ //instruções de 2 bytes
        cpu->mar = cpu->pc;
        cpu->mbr = (cpu->mbr << 8) | ram->endereco[cpu->mar];
        cpu->pc++;

        if(tamanho_opcodes[cpu->ir] == 3){ //instruções de 3 bytes
            cpu->mar = cpu->pc;
            cpu->mbr = (cpu->mbr << 8) | ram->endereco[cpu->mar];
            cpu->pc++;
    }
    cpu->mbr = cpu->mbr & 0b00000000111111111111111111111111; //Limpeza somente para garantir que o MBR esteja usando só seus  24 bits
    return(tamanho_opcodes[cpu->ir]);
}

void decodificar_instrucao(CPU* cpu, unsigned char tamanho_instrucao){ //Decodificação específica das instruções,
    if(cpu == NULL)                                                 //o objetivo principal aqui é modificar os registradores necessários
        return;)                                                 //e preparar para a correta fase de EXECUÇÃO
    switch(tamanho_instrucao){
    case 1: //Se encaixam aqui somente hlt,nop, e not
        if(cpu->ir == NOT) //Apenas a instrução not necessita de algum outro registrador
        cpu->ro0 = cpu->mbr & 0b00000111;
        break;

    case 2: //Todas as instruções de aritmética entre dois registradores gerais
            //ou operações lógicas (Exceto not, que é unária) --> ldr .. xor
        cpu->ro0 = (cpu->mbr >> 8) & 0b00000111;
        cpu->ro1 = (cpu->mbr >> 5) & 0b00000111;
        break;


    case 3: //Todas as instruções de aritmética entre um registrador geral e um imediato
            //ou as operações de load e store ou então as instruções de jumps.
        if(cpu->ir <= JMP){ //IR possui um opcode de algum dos jumps
            cpu->mar = cpu->mbr;
        }else{
            cpu->ro0 = (cpu->mbr >> 16) & 0b00000111;
            if(cpu->ir <= ST)//IR possui ou o opcode do store ou do load
                cpu->mar = cpu->mbr;
            else //IR possui um opcode de operação aritmética com imediato
                cpu->imm = cpu->mbr;
        }
    }
}


void executar_instrucao(CPU* cpu,Memoria* ram){

}



