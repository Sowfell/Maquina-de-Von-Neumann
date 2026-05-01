#include "memoria.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Memoria* iniciar_memoria(){
    Memoria *memoria = (Memoria*)malloc(sizeof(Memoria));
    if(memoria != NULL)
        for(int i=0; i<256; i++)
            memoria->endereco[i] = 0;
    return memoria;
}
//
//void carregar_programa(Memoria* ram, char *caminho_programa){
//    FILE *arquivo = fopen(caminho_programa, "r");
//    if (arquivo == NULL) {
//        perror("Erro ao abrir o programa");
//    }
//
//    char linha[256]; // buffer para armazenar a linha
//
//    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
//        //Separa��o da String
//        char endereco[4];
//        char tipo;
//        char informacao[20];
//        int count=0;
//        for(int i=0;linha[count]!=';';i++,count++){
//            endereco[i]=linha[i];
//            endereco[i+1] = '\0';
//        }
//        count++;
//        tipo=linha[count];
//        count+=2;
//        for(int i=0;linha[count]!='\n';i++,count++){
//            informacao[i]=linha[count];
//            informacao[i+1] = '\0';
//        }
//        //convers�o para valores num�ricos
//        unsigned int end=(unsigned int)strtol(endereco,NULL,16);
//        printf("%x\n",end);
//    }
//    fclose(arquivo);
//}
//

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
    char buffer[256];

    while(fgets(buffer,sizeof(buffer),arquivo)!=NULL){
         unsigned char tamanhoBytes = 1;
         unsigned int endereco = 0;
         unsigned char tipo=0;
         unsigned char opcode=0;
         unsigned char rX=0;
         unsigned char rY=0;
         unsigned int z=0;
         unsigned char imm=0;

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
                if(opcode <= 0x01)                          // hlt, nop
                {
                    break;
                }
                else if(opcode <= 0x0C)                     // 2 registradores
                {
                    rX = codificarRegistrador(token);
                }
                else if(opcode == 0x0D)                     // not
                {
                    rX = codificarRegistrador(token);
                }
                else if(opcode <= 0x14)                     // saltos (1 endereço)
                    z = (unsigned char)strtol(token, NULL, 16);
                else if(opcode <= 0x16)                     // ld, st (registrador + endereço)
                    rX = codificarRegistrador(token);
                else if(opcode <= 0x1D)                     // imediatos
                    rX = codificarRegistrador(token);
                  break;
            case 4:
    if(opcode <= 0x0C)                              // 2 registradores
        rY = codificarRegistrador(token);
    else if(opcode == 0x15 || opcode == 0x16){      // ld, st (endereço)
        z = (unsigned char)strtol(token, NULL, 16);
        printf("z = %X\n", z);
    }
    else if(opcode >= 0x17 && opcode <= 0x1D)       // imediatos
        imm = (unsigned char)strtol(token, NULL, 16);
    break;
default:
    break;
}
        }
        if(tipo == 'i'){
    unsigned int palavra = 0;

    if(opcode <= 0x01)                              // hlt, nop
        palavra = opcode << 19;
    else if(opcode <= 0x0D)                         // 2 registradores ou not
        palavra = (opcode << 19) | (rX << 16) | (rY << 13);
    else if(opcode <= 0x14)                         // saltos
        palavra = (opcode << 19) | z;
    else if(opcode <= 0x16)                         // ld, st
        palavra = (opcode << 19) | (rX << 16) | z;
    else                                            // imediatos
        palavra = (opcode << 19) | (rX << 16) | imm;

    ram->endereco[endereco]   = (palavra >> 16) & 0xFF;
    ram->endereco[endereco+1] = (palavra >> 8)  & 0xFF;
    ram->endereco[endereco+2] =  palavra        & 0xFF;
}
    }

}
