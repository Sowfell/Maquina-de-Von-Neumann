#include "instrucoes.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>

//instru��es de 8 bits
int hlt(){
    return 0;
}

void nop(){
    return;
}

//instru��es de 16 bits

void ldr(CPU* cpu, Memoria* ram){
    if(cpu==NULL || ram==NULL )
        return;
    cpu->mar = cpu->reg[cpu->ro1];
    cpu->mbr = ram->endereco[cpu->mar];
    cpu->mar++;
    cpu->mbr = (cpu->mbr << 8)|ram->endereco[cpu->mar];
    cpu->reg[cpu->ro0] = cpu->mbr;
}

void str(CPU* cpu, Memoria* ram){
    if(cpu==NULL || ram==NULL )
        return;
    cpu->mar = cpu->reg[cpu->ro1];
    cpu->mbr = cpu->reg[cpu->ro0];
    ram->endereco[cpu->mar] = cpu->mbr >> 8;
    cpu->mar++;
    ram->endereco[cpu->mar] = cpu->mbr;
}

void add(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] += cpu->reg[cpu->ro1];
}

void sub(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] -= cpu->reg[cpu->ro1];
}

void mul(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] *= cpu->reg[cpu->ro1];
}

void _div(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] /= cpu->reg[cpu->ro1];
}

void cmp(CPU* cpu){
    if(cpu==NULL)
        return;
    if(cpu->reg[cpu->ro0] == cpu->reg[cpu->ro1])
        cpu->e = 1;
    else
        cpu->e = 0;

    if(cpu->reg[cpu->ro0] < cpu->reg[cpu->ro1])
        cpu->l = 1;
    else
        cpu->l = 0;

    if(cpu->reg[cpu->ro0] > cpu->reg[cpu->ro1])
        cpu->g = 1;
    else
        cpu->g = 0;
}

void movr(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] = cpu->reg[cpu->ro1];
}

void and(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] = cpu->reg[cpu->ro0] & cpu->reg[cpu->ro1];
}

void or(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] = cpu->reg[cpu->ro0] | cpu->reg[cpu->ro1];
}

void xor(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] = cpu->reg[cpu->ro0] ^ cpu->reg[cpu->ro1];
}

//instru��o de 8 bits
void not(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] = !cpu->reg[cpu->ro0];
}

//instru��es de 24 bits
void je(CPU* cpu){
    if(cpu == NULL)
        return;
    if(cpu->e)
        cpu->pc = cpu->mar;
}

void jne(CPU* cpu){
    if(cpu == NULL)
        return;
    if(!cpu->e)
        cpu->pc = cpu->mar;
}

void jl(CPU* cpu){
    if(cpu == NULL)
        return;
    if(cpu->l)
        cpu->pc = cpu->mar;
}

void jle(CPU* cpu){
    if(cpu == NULL)
        return;
    if(cpu->e || cpu->l)
        cpu->pc = cpu->mar;
}

void jg(CPU* cpu){
    if(cpu == NULL)
        return;
    if(cpu->g)
        cpu->pc = cpu->mar;
}

void jge(CPU* cpu){
    if(cpu == NULL)
        return;
    if(cpu->e || cpu->g)
        cpu->pc = cpu->mar;
}

void jmp(CPU* cpu){
    if(cpu == NULL)
        return;
    cpu->pc = cpu->mar;
}

//instru��es de 24 bits
void ld(CPU* cpu, Memoria* ram){
    if(cpu==NULL || ram==NULL )
        return;
    //MAR j� est� com o endere�o correto, isso foi realizado na etapa de decodifica��o
    cpu->mbr = ram->endereco[cpu->mar];
    cpu->mar++;
    cpu->mbr = (cpu->mbr << 8)|ram->endereco[cpu->mar];
    cpu->reg[cpu->ro0] = cpu->mbr;
}

void st(CPU* cpu, Memoria* ram){
    if(cpu==NULL || ram==NULL )
        return;
    //MAR j� est� com o endere�o correto, isso foi realizado na etapa de decodifica��o
    cpu->mbr = cpu->reg[cpu->ro0];
    ram->endereco[cpu->mar] = cpu->mbr >> 8;
    cpu->mar++;
    ram->endereco[cpu->mar] = cpu->mbr;
}

void movi(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] = cpu->imm;
}

void addi(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] += cpu->imm;
}

void subi(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] -= cpu->imm;
}

void muli(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] *= cpu->imm;
}

void divi(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] /= cpu->imm;
}

void lsh(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] = cpu->reg[cpu->ro0] << cpu->imm;
}

void rsh(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->reg[cpu->ro0] = cpu->reg[cpu->ro0] >> cpu->imm;
}




