#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "memoria.h"
#include "interface.h"

int main() {
    int *controle_programa = 0;
    CPU *cpu = iniciar_cpu();
    Memoria *ram = iniciar_memoria();
    iniciar_programa(cpu,ram,controle_programa);

    output(cpu,ram);


    return 0;
}
