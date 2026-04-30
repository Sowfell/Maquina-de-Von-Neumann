#ifndef INSTRUCOES_H
#define INSTRUCOES_H
#include "cpu.h"
/*
 * Esse arquivo está especificando somente as instruções em sua fase de execução:
 * a busca e a decodificação são realizadas pela própria CPU em seu respectivo arquivo
 */

//instruções de 8 bits
void hlt();
void nop(CPU* cpu);
//instruções de 16 bits
void ldr(CPU* cpu,unsigned char rX, unsigned char rY, Memoria* ram);
void str(CPU* cpu,unsigned char rX, unsigned char rY, Memoria* ram);
void add(CPU* cpu,unsigned char rX, unsigned char rY);
void sub(CPU* cpu,unsigned char rX, unsigned char rY);
void mul(CPU* cpu,unsigned char rX, unsigned char rY);
void _div(CPU* cpu,unsigned char rX, unsigned char rY);
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

#endif
