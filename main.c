#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "memoria.h"


void printBinario(int n) {
    // Loop de 31 até 0 para um inteiro de 32 bits
    for (int i = 16; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}



int main() {


//    mbr = 0b111100001111000011110000;
//
//    ir = mbr >> 19;//pega os 5 primeiros bits do mbr
//
//
//    printBinario(ir);
//
//    }



    return 0;
}
