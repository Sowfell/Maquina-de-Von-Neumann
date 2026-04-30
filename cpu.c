#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "memoria.h"
#include "instrucoes.h"

//Esse é um vetor que serve para indicar quantos bytes são necessários buscar
//da memória de acordo com cada instrução, cada posição do vetor equivale à uma
//instrução do conjunto completo, de modo que já estão na ordem correta. Ou seja, por exemplo
//hlt que tem opcode 0b00000 equivale a posição 1, nop que tem 0b00001 está na posição 2, e assim por diante

unsigned char tamanho_opcodes[30] = {1,1, //hlt .. nop
                                     2,2,2,2,2,2,2,2,2,2,2, //ldr ... xor
                                     1, // not
                                     3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}; //je .. rsh

CPU* iniciar_cpu(){
    CPU *cpu = (CPU*)malloc(sizeof(cpu));
    if(cpu != NULL){
        cpu->pc = 0;
    }
    return cpu;
}

void iniciar_programa(CPU* cpu,Memoria* ram,int *controle_ciclo){
    if(cpu == NULL || ram == NULL)
        return;

    unsigned char t_instrucao = 0;
    int programa_executando = 1;
    int *proximo_ciclo = controle_ciclo;
    char confirmar_proximo_ciclo;

    while(programa_executando){
        if(*proximo_ciclo){
            t_instrucao = buscar_instrucao(cpu,ram);
            decodificar_instrucao(cpu, t_instrucao);
            programa_executando = executar_instrucao(cpu,ram);
            *proximo_ciclo = 0;
        }
        scanf(" %c", &confirmar_proximo_ciclo);
        if(confirmar_proximo_ciclo == '\n')
            *proximo_ciclo = 1;
        confirmar_proximo_ciclo = '0';
    }
}

unsigned char buscar_instrucao(CPU* cpu,Memoria* ram){ //A busca também faz uma pré-decodificação
    if(cpu == NULL || ram == NULL)              //que apenas analisa quantos bytes ainda devem ser buscados
        return 0;
    cpu->mar = cpu->pc;
    cpu->mbr = ram->endereco[cpu->mar]; //Pega o Opcode da instrução
    cpu->ir = cpu->mbr >> 3;

    //Não é preciso verificar se a instrução tem somente 1 byte, se esse for o caso
    //a busca já está completa
    if(tamanho_opcodes[cpu->ir] < 1 || tamanho_opcodes[cpu->ir] > 3){
        perror("Erro de codificao de instrucao, opcode invalido");
        return 0; //Só uma verificação de segurança
    }

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

    }
    cpu->mbr = cpu->mbr & 0b00000000111111111111111111111111; //Limpeza somente para garantir que o MBR esteja usando só seus  24 bits
    return(tamanho_opcodes[cpu->ir]);
}

void decodificar_instrucao(CPU* cpu, unsigned char tamanho_instrucao){ //Decodificação específica das instruções,
    if(cpu == NULL)                                                 //o objetivo principal aqui é modificar os registradores necessários
        return;                                                 //e preparar para a correta fase de EXECUÇÃO
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


int executar_instrucao(CPU* cpu,Memoria* ram){
    if(cpu == NULL || ram == NULL)
        return 0;
    int valorRetorno = 1;
    switch(cpu->ir){
    case HLT:
        valorRetorno = hlt();
        break;

    case NOP:
        nop(cpu,ram);
        break;

    case LDR:
        ldr(cpu,ram);
        break;

    case STR:
        str(cpu,ram);
        break;

    case ADD:
        add(cpu);
        break;

    case SUB:
        sub(cpu);
        break;

    case MUL:
        mul(cpu);
        break;

    case DIV:
        _div(cpu);
        break;

    case CMP:
        cmp(cpu);
        break;

    case MOVR:
        movr(cpu);
        break;

    case AND:
        and(cpu);
        break;

    case OR:
        or(cpu);
        break;

    case XOR:
        xor(cpu);
        break;

    case NOT:
        not(cpu);
        break;

    case JE:
        je(cpu);
        break;

    case JNE:
        jne(cpu);
        break;

    case JL:
        jl(cpu);
        break;

    case JLE:
        jle(cpu);
        break;

    case JG:
        jg(cpu);
        break;

    case JGE:
        jge(cpu);
        break;

    case JMP:
        jmp(cpu);
        break;

    case LD:
        ld(cpu,ram);
        break;

    case ST:
        st(cpu,ram);
        break;

    case MOVI:
        movi(cpu);
        break;

    case ADDI:
        addi(cpu);
        break;

    case SUBI:
        subi(cpu);
        break;

    case MULI:
        muli(cpu);
        break;

    case DIVI:
        divi(cpu);
        break;

    case LSH:
        lsh(cpu);
        break;

    case RSH:
        rsh(cpu);
        break;

    }
    return valorRetorno;

}



