#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "memoria.h"
#include "interface.h"

int main() {
    int teste = 1;
    int *controle_programa = &teste;
    CPU *cpu = iniciar_cpu();
    Memoria *ram = iniciar_memoria();
    output(cpu,ram);
    ler("fibonacci_assembly.txt",ram);
    iniciar_programa(cpu,ram,controle_programa);
    
    return 0;
}
