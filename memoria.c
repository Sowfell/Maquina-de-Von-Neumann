#include "memoria.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Memoria* iniciar_memoria(){
    Memoria *memoria = (Memoria*)malloc(sizeof(memoria));
    if(memoria != NULL)
        for(int i=0; i<256; i++)
            memoria->endereco[i] = 0;
    return memoria;
}

void carregar_programa(Memoria* ram, char *caminho_programa){
    FILE *arquivo = fopen(caminho_programa, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o programa");
    }

    char linha[256]; // buffer para armazenar a linha

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        //Separação da String
        char endereco[4];
        char tipo;
        char informacao[20];
        int count=0;
        for(int i=0;linha[count]!=';';i++,count++){
            endereco[i]=linha[i];
            endereco[i+1] = '\0';
        }
        count++;
        tipo=linha[count];
        count+=2;
        for(int i=0;linha[count]!='\n';i++,count++){
            informacao[i]=linha[count];
            informacao[i+1] = '\0';
        }
        //conversão para valores numéricos
        unsigned int end=(unsigned int)strtol(endereco,NULL,16);
        printf("%x\n",end);
    }
    fclose(arquivo);
}


unsigned char codificarInstrucao(char* ins){
   if(strcmp("hlt",ins)==0) return HLT;
   if(strcmp("nop",ins)==0) return NOP;
   if(strcmp("ldr",ins)==0) return LDR;
   if(strcmp("str",ins)==0) return STR;
   if(strcmp("add",ins)==0) return ADD;
   if(strcmp("sub",ins)==0) return SUB;
   if(strcmp("mul",ins)==0) return MUL;
   if(strcmp("div",ins)==0) return DIV;
   if(strcmp("cmp",ins)==0) return CMP;
   if(strcmp("movr",ins)==0) return MOVR;
   if(strcmp("and",ins)==0) return AND;
   if(strcmp("or",ins)==0) return OR;
   if(strcmp("xor",ins)==0) return XOR;
   if(strcmp("not",ins)==0) return NOT;
   if(strcmp("je",ins)==0) return JE;
   if(strcmp("jne",ins)==0) return JNE;
   if(strcmp("jl",ins)==0) return JL;
   if(strcmp("jle",ins)==0) return JLE;
   if(strcmp("jg",ins)==0) return JG;
   if(strcmp("jge",ins)==0) return JGE;
   if(strcmp("jmp",ins)==0) return JMP;
   if(strcmp("ld",ins)==0) return LD;
   if(strcmp("st",ins)==0) return ST;
   if(strcmp("movi",ins)==0) return MOVI;
   if(strcmp("addi",ins)==0) return ADDI;
   if(strcmp("subi",ins)==0) return SUBI;
   if(strcmp("muli",ins)==0) return MULI;
   if(strcmp("divi",ins)==0) return DIVI;
   if(strcmp("lsh",ins)==0) return LSH;
   if(strcmp("rsh",ins)==0) return RSH;
}

unsigned char codificarRegistrador(char* registrador){
   if(strcmp("r0",registrador)==0) return 0x0;
   if(strcmp("r1",registrador)==0) return 0x1;
   if(strcmp("r2",registrador)==0) return 0x2;
   if(strcmp("r3",registrador)==0) return 0x3;
   if(strcmp("r4",registrador)==0) return 0x4;
   if(strcmp("r5",registrador)==0) return 0x5;
   if(strcmp("r6",registrador)==0) return 0x6;
   if(strcmp("r7",registrador)==0) return 0x7;
}

void ler(char* path,Memoria* ram){

    FILE* arquivo = fopen(path,"r");
    if(arquivo==NULL){
        printf("Erro ao abrir o programa\n");
        exit(1);
    }

    unsigned char tamanhoBytes = 1;
    unsigned int endereco = 0;
    unsigned char tipo;
    unsigned char opcode;
    unsigned char rX;
    unsigned char rY;
    unsigned char z;
    unsigned char imm;

    char buffer[256];

    while(fgets(buffer,sizeof(buffer),arquivo)!=NULL){
        char* token = strtok(buffer,"; ,");
        int count = 0;
        endereco = (unsigned int)strtol(token,NULL,16);

        while(token!=NULL && count<5){ //Se por acaso for mais de 5 tokens, mude AQUI count<X
            token=strtok(NULL,", ;\n");
            count++;
            switch(count){
            case 1:
                tipo = token[0];
                break;
            case 2:
                if(tipo == 'd'){
                    ram->endereco[endereco] = (unsigned int)strtol(token,NULL,16) >> 8;
                    ram->endereco[endereco+1] = (unsigned int)strtol(token,NULL,16) & 0b0000000011111111;
                }

                else if(tipo == 'i'){
                    opcode = codificarInstrucao(token);
                }
                break;
            case 3:
                if(opcode <= 1) // instruções sem registradores, endereços, etc.
                    break;

                else if(opcode <= 12) //instruções com 2 registradores
                    rX = codificarRegistrador(token);

                else if(opcode == 13) //instrução com 1 registrador
                    rX = codificarRegistrador(token);

                else if(opcode <= 20) //instrução com 1 endereço de memória
                    z = (unsigned char)strtol(token,NULL,16);

                else if(opcode <= 22) //instrução com 1 registrador e 1 endereço de memória
                    rX = codificarRegistrador(token);

                else if(opcode <= 29) //instrução com 1 registrador e 1 imediato
                    rX = codificarRegistrador(token);

            case 4:
                if(opcode >= 1 && opcode <= 12) //instruções com 2 registradores
                    rY = codificarRegistrador(token);

                else if(opcode > 20 && opcode <= 22) //instrução com 1 registrador e 1 endereço de memória
                    z = (unsigned char)strtol(token,NULL,16);

                else if(opcode <= 29) //instrução com 1 registrador e 1 imediato
                    imm = (unsigned char)strtol(token,NULL,16);
                break;

            default:
                break;
            }
        }
    }

}
