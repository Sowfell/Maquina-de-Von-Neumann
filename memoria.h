#ifndef MEMORIA_H
#define MEMORIA_H

struct memoria{
    unsigned char endereco[256];
};

typedef struct memoria Memoria;

Memoria* iniciar_memoria();
void carregar_programa(Memoria* ram,char *caminho_programa);

#endif // MEMORIA_H
