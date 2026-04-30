#ifndef INSTRUCOES_H
#define INSTRUCOES_H
#include "cpu.h"
/*
 * Esse arquivo está especificando somente as instruções em sua fase de execução:
 * a busca e a decodificação são realizadas pela própria CPU em seu respectivo arquivo
 */

//instruções de 8 bits
int hlt();
void nop();
//instruções de 16 bits
void ldr(CPU* cpu, Memoria* ram);
void str(CPU* cpu, Memoria* ram);
void add(CPU* cpu);
void sub(CPU* cpu);
void mul(CPU* cpu);
void _div(CPU* cpu);
void cmp(CPU* cpu);
void movr(CPU* cpu);
void and(CPU* cpu);
void or(CPU* cpu);
void xor(CPU* cpu);
//instrução de 8 bits
void not(CPU* cpu);
//instruções de 24 bits
void je(CPU* cpu);
void jne(CPU* cpu);
void jl(CPU* cpu);
void jle(CPU* cpu);
void jg(CPU* cpu);
void jge(CPU* cpu);
void jmp(CPU* cpu);
//instruções de 24 bits
void ld(CPU* cpu, Memoria* ram);
void st(CPU* cpu, Memoria* ram);
void movi(CPU* cpu);
void addi(CPU* cpu);
void subi(CPU* cpu);
void muli(CPU* cpu);
void divi(CPU* cpu);
void lsh(CPU* cpu);
void rsh(CPU* cpu);

#endif
