#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

#define N 100

struct fila{
    int dados[N];
    int inicio;
    int fim;
    int qntd;
};

Fila Iniializar(){
    Fila f = (Fila)malloc(sizeof(struct fila));
    f->inicio = 0;
    f->fim = 0;
    f->qntd = 0;
    return f;
}

Fila Destruir(Fila f){
    free(f);
    return NULL;
}

int Inserir(Fila f, int x){
    if(f->qntd == N)
        return 0;  // fila cheia
    f->dados[f->fim] = x;
    f->fim = (f->fim + 1) % N;
    f->qntd++;
    return 1;
}

int Remover(Fila f, int *x){
    if(f->qntd == 0)
        return 0;  // fila vazia
    *x = f->dados[f->inicio];
    f->inicio= (f->inicio + 1) % N;
    f->qntd--;
    return 1;
}

void Imprimir(Fila f){
    if(f->qntd == 0)
        printf("Fila vazia \n");
    else{
        printf("Fila: ");
        for(int i = 0; i < f->qntd; i++){
            int index = (f->inicio + 1) % N;
            printf("%d ", f->dados[index]);
        }
    }
}