#include "instrucoes.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>

//instruções de 8 bits
void hlt(){}
void nop(CPU* cpu){
    if(cpu==NULL)
        return;
    cpu->pc++;
}
void ldr(CPU* cpu,unsigned char rX, unsigned char rY, Memoria* ram){
    if(cpu==NULL || ram==NULL )
        return;
    cpu->pc +=2;
    cpu->mar = rY[0];
    cpu->mbr = ram->endereco[mar];
    cpu->mbr = (cpu->mbr << 8)|ram[mar+1];
    switch(rX){
        case 0b000:
            cpu->r0[0] = cpu->mbr;
            break;
        case 0b001:
            cpu->r1[0] = cpu->mbr;
            break;
        case 0b010:
            cpu->r2[0] = cpu->mbr;
            break;
        case 0b011:
            cpu->r3[0] = cpu->mbr;
            break;
        case 0b100:
            cpu->r4[0] = cpu->mbr;
            break;
        case 0b101:
            cpu->r5[0] = cpu->mbr;
            break;
        case 0b110:
            cpu->r6[0] = cpu->mbr;
            break;
        case 0b111:
            cpu->r6[0] = cpu->mbr;
            break;
    }


}













//instruções de 16 bits

void str(CPU* cpu,unsigned char rX, unsigned char rY, Memoria* ram);
void add(CPU* cpu,unsigned char rX, unsigned char rY);
void sub(CPU* cpu,unsigned char rX, unsigned char rY);
void mul(CPU* cpu,unsigned char rX, unsigned char rY);
void div(CPU* cpu,unsigned char rX, unsigned char rY);
void cmp(CPU* cpu,unsigned char rX, unsigned char rY);
void movr(CPU* cpu,unsigned char rX, unsigned char rY);
void and(CPU* cpu,unsigned char rX, unsigned char rY);
void or(CPU* cpu,unsigned char rX, unsigned char rY);
void xor(CPU* cpu,unsigned char rX, unsigned char rY);
//instrução de 8 bits
void not(CPU* cpu,unsigned char rX, unsigned char rY);
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
