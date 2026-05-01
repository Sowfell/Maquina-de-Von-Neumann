#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "memoria.h"
#ifdef _WIN32
#include <windows.h>
void set_cor(int cor){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}
#define BLACK   set_cor(0)
#define RED     set_cor(12)
#define GREEN   set_cor(10)
#define YELLOW  set_cor(14)
#define BLUE    set_cor(9)
#define MAGENTA set_cor(13)
#define CYAN    set_cor(11)
#define WHITE   set_cor(15)
#define RESET   set_cor(7)

#else

#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define ITALIC  "\033[3m"
#define UNDERLINE "\033[4m"
#define BLINK   "\033[5m"
#define REVERSE "\033[7m"
#define HIDDEN  "\033[8m"
#define STRIKE  "\033[9m"
#define PRED    CYAN BOLD ITALIC

#endif


void output(CPU* cpu, Memoria* memoria){
    system("clear");
    int x=45; // Parametro médio para espaçamento do print nos FORs
    printf(BOLD MAGENTA"| CPU\n"RESET);
    printf(BOLD MAGENTA" _"RESET);
    for(int i=0;i<x;i++) printf(BOLD MAGENTA"_"RESET);
        printf(BOLD MAGENTA"\n|"); for(int i=0;i<x;i++) printf(HIDDEN" "RESET); printf(BOLD MAGENTA" |"RESET);
        printf(BOLD MAGENTA"\n| "RESET PRED" R0:"RESET BLUE"  %04X  "PRED"R1:"RESET BLUE"  %04X  "PRED"R2:"RESET BLUE"  %04X  "PRED"R3:"RESET BLUE"  %04X"RESET MAGENTA BOLD"  |",cpu->reg[0],cpu->reg[1],cpu->reg[2],cpu->reg[3]);
        printf(BOLD MAGENTA"\n| "RESET PRED" R4:"RESET BLUE"  %04X  "PRED"R5:"RESET BLUE"  %04X  "PRED"R6:"RESET BLUE"  %04X  "PRED"R7:"RESET BLUE"  %04X"RESET MAGENTA BOLD"  |",cpu->reg[4],cpu->reg[5],cpu->reg[6],cpu->reg[7]);
        printf(BOLD MAGENTA"\n| "RESET PRED" MBR:"RESET BLUE" %08X "PRED"MAR:"RESET BLUE" %04X "PRED"IMM:"RESET BLUE" %04X "PRED"PC:"RESET BLUE" %04X"RESET MAGENTA BOLD"  |",cpu->mbr,cpu->mar,cpu->imm,cpu->pc);
        printf(BOLD MAGENTA"\n| "RESET PRED" IR:"RESET BLUE" %02X        "PRED"RO0:"RESET BLUE" %X        "PRED"RO1:"RESET BLUE" %X "RESET MAGENTA BOLD"         |\n",cpu->ir,cpu->ro0,cpu->ro1);
        printf(BOLD MAGENTA"| "RESET PRED" E:  "RESET BLUE" %X        "PRED"L:  "RESET BLUE" %X        "PRED"G:  "RESET BLUE" %X "RESET MAGENTA BOLD"         |\n",cpu->e,cpu->l,cpu->g);

        printf("|");
    for(int i=0;i<x+1;i++) printf(BOLD MAGENTA"_"RESET);
        printf(BOLD MAGENTA"|"RESET);



        printf("\n\n"BOLD MAGENTA"| MEMORIA:\n"RESET);
        printf(BOLD MAGENTA" _"RESET);
    for(int i=0;i<x+8;i++) printf(BOLD MAGENTA"_"RESET);
        printf(BOLD MAGENTA"\n|");
    for(int i=0;i<x+9;i++) printf(" ");
        printf(BOLD MAGENTA"|");
        printf(BOLD MAGENTA"\n|     "RESET);
    for(int i=0; i<16;i++) printf(CYAN BOLD ITALIC"0%X "RESET"",i);
        printf(BOLD MAGENTA" |\n"RESET);
    for(int i=0;i<16;i++){
        printf(BOLD MAGENTA"|  "RESET CYAN BOLD ITALIC"%X0"RESET"",i);
        for(int j=0;j<16;j++){
            printf(BLUE " %02X"RESET"",memoria->endereco[i*16+j]);
        }
        printf(BOLD MAGENTA"  |\n"BOLD MAGENTA);
    }
    printf("|");
    for(int i=0;i<x+9;i++)
        printf("_");
    printf("|\n\n"RESET);
    printf(BOLD ITALIC GREEN"Pressione Enter para continuar os ciclos de execução e CTRL + C para finalizar o programa\n"RESET);
}
