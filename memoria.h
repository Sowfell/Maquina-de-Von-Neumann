#ifndef MEMORIA_H
#define MEMORIA_H

struct memoria{
    unsigned char endereco[256];
};

typedef struct memoria Memoria;

Memoria* iniciar_memoria();
void ler(char* path,Memoria* ram);

#endif // MEMORIA_H
