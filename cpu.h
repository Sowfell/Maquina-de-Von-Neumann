#ifndef CPU_H
#define CPU_H
#include "memoria.h"

enum opcodes{
    HLT = 0x0,
    NOP = 0x1,
    LDR = 0x2,
    STR = 0x3,
    ADD = 0x4,
    SUB = 0x5,
    MUL = 0x6,
    DIV = 0x7,
    CMP = 0x8,
    MOVR = 0x9,
    AND = 0xA,
    OR = 0xB,
    XOR = 0xC,
    NOT = 0xD,
    JE = 0xE,
    JNE = 0xF,
    JL = 0x10,
    JLE = 0x11,
    JG = 0x12,
    JGE = 0x13,
    JMP = 0x14,
    LD = 0x15,
    ST = 0x16,
    MOVI = 0x17,
    ADDI = 0x18,
    SUBI = 0x19,
    MULI = 0x1A,
    DIVI = 0x1B,
    LSH = 0x1C,
    RSH = 0x1D,
};

struct cpu{
    unsigned int mbr; //32 bits no total; Ser�o usados somente 24bits
    unsigned short int mar; //16 bits
    unsigned char ir; //8bits
    unsigned char ro0,ro1; //8bits
    unsigned short int imm; //16 bits
    unsigned short int pc; //16 bits, por padr�o ele sempre vai come�ar apontando para o endere�o 0x0
    unsigned char e, l, g; //8bits cada, s�o apenas flags de compara��o
    unsigned short int reg[8]; //8 registradores de 16bits;
};

typedef struct cpu CPU;

CPU* iniciar_cpu();
void iniciar_programa(CPU* cpu,Memoria* ram,int *controle_ciclo);
unsigned char buscar_instrucao(CPU* cpu,Memoria* ram);
void decodificar_instrucao(CPU* cpu, unsigned char tamanho_instrucao);
int executar_instrucao(CPU* cpu,Memoria* ram);


#endif // CPU_H
