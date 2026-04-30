#include "instrucoes.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>

void carregar_registrador_geral(CPU* cpu,unsigned char codRegistrador, unsigned short int valor){
        switch(codRegistrador){
        case 0b000:
            cpu->r0[0] = valor;
            break;
        case 0b001:
            cpu->r1[0] = valor;
            break;
        case 0b010:
            cpu->r2[0] = valor;
            break;
        case 0b011:
            cpu->r3[0] = valor;
            break;
        case 0b100:
            cpu->r4[0] = valor;
            break;
        case 0b101:
            cpu->r5[0] = valor;
            break;
        case 0b110:
            cpu->r6[0] = valor;
            break;
        case 0b111:
            cpu->r6[0] = valor;
            break;
    }
}
unsigned short int ler_registrador_geral(CPU* cpu,unsigned char codRegistrador){
        switch(codRegistrador){
        case 0b000:
            return cpu->r0[0];

        case 0b001:
            return cpu->r1[0];

        case 0b010:
            return cpu->r2[0];

        case 0b011:
            return cpu->r3[0];

        case 0b100:
            return cpu->r4[0];

        case 0b101:
            return cpu->r5[0];

        case 0b110:
            return cpu->r6[0];

        case 0b111:
            return cpu->r7[0];
        default:
            return 0;

    }
}


//CORREÇÃO EXTREMAMENTE IMPORTANTE!!!!, PARAR DE INCREMENTAR O PC NESSA PARTE DO CÓDIGO
//instruções de 8 bits
void hlt(){
    return;
}

void nop(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->pc++;
}

//instruções de 16 bits

void ldr(CPU* cpu,unsigned char rX, unsigned char rY, Memoria* ram){
    if(cpu==NULL || ram==NULL )
        return;
    cpu->pc +=2;
    cpu->mar = ler_registrador_geral(cpu,rY);
    cpu->mbr = ram->endereco[cpu->mar];
    cpu->mbr = (cpu->mbr << 8)|ram->endereco[cpu->mar+1];
    carregar_registrador_geral(cpu,rX,cpu->mbr);
}

void str(CPU* cpu,unsigned char rX, unsigned char rY, Memoria* ram){
    if(cpu==NULL || ram==NULL )
        return;
    cpu->pc +=2;
    cpu->mar = ler_registrador_geral(cpu,rY);
    cpu->mbr = ler_registrador_geral(cpu,rX);
    ram->endereco[cpu->mar] = cpu->mbr >> 8;
    ram->endereco[cpu->mar+1] = cpu->mbr;
}

void add(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc += 2;
    carregar_registrador_geral(cpu,rX,ler_registrador_geral(cpu,rX) + ler_registrador_geral(cpu,rY));
}

void sub(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc += 2;
    carregar_registrador_geral(cpu,rX,ler_registrador_geral(cpu,rX) - ler_registrador_geral(cpu,rY));
}

void mul(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc += 2;
    carregar_registrador_geral(cpu,rX,ler_registrador_geral(cpu,rX) * ler_registrador_geral(cpu,rY));
}

void _div(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc += 2;
    carregar_registrador_geral(cpu,rX,ler_registrador_geral(cpu,rX) / ler_registrador_geral(cpu,rY));
}

void cmp(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc += 2;
    if(ler_registrador_geral(cpu,rX) == ler_registrador_geral(cpu,rX))
        cpu->e = 1;
    else
        cpu->e = 0;

    if(ler_registrador_geral(cpu,rX) < ler_registrador_geral(cpu,rX))
        cpu->l = 1;
    else
        cpu->l = 0;

    if(ler_registrador_geral(cpu,rX) > ler_registrador_geral(cpu,rX))
        cpu->g = 1;
    else
        cpu->g = 0;
}
void movr(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc += 2;
    carregar_registrador_geral(cpu,rX,ler_registrador_geral(cpu,rY));
}

void and(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc += 2;
    carregar_registrador_geral(cpu,rX,ler_registrador_geral(cpu,rX) & ler_registrador_geral(cpu,rY));
}

void or(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc += 2;
    carregar_registrador_geral(cpu,rX,ler_registrador_geral(cpu,rX) | ler_registrador_geral(cpu,rY));
}

void xor(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc += 2;
    carregar_registrador_geral(cpu,rX,ler_registrador_geral(cpu,rX) ^ ler_registrador_geral(cpu,rY));
}

//instrução de 8 bits
void not(CPU* cpu,unsigned char rX, unsigned char rY){
    if(cpu==NULL)
        return;
    cpu->pc ++;
    carregar_registrador_geral(cpu,rX,!ler_registrador_geral(cpu,rX));
}

//instruções de 24 bits
void je(CPU* cpu, unsigned char endereco);
void jne(CPU* cpu, unsigned char endereco);
void jl(CPU* cpu, unsigned char endereco);
void jle(CPU* cpu, unsigned char endereco);
void jg(CPU* cpu, unsigned char endereco);
void jge(CPU* cpu, unsigned char endereco);
void jmp(CPU* cpu, unsigned char endereco);
//instruções de 24 bits
void ld(CPU* cpu, unsigned char rX, unsigned char endereco, Memoria* ram);
void st(CPU* cpu, unsigned char rX, unsigned char endereco, Memoria* ram);
void movi(CPU* cpu, unsigned char rX, unsigned char imm);
void addi(CPU* cpu, unsigned char rX, unsigned char imm);
void subi(CPU* cpu, unsigned char rX, unsigned char imm);
void muli(CPU* cpu, unsigned char rX, unsigned char imm);
void divi(CPU* cpu, unsigned char rX, unsigned char imm);
void lsh(CPU* cpu, unsigned char rX, unsigned char imm);
void rsh(CPU* cpu, unsigned char rX, unsigned char imm);




