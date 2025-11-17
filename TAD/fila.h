#include <stdio.h>
#include <stdlib.h>

#ifndef FILA_H
#define FILA_H

typedef struct fila *Fila;

Fila Iniializar();

Fila Destruir(Fila f);

int Inserir(Fila f, int x);

int Remover(Fila f, int *x);

void Imprimir(Fila f);

#endif