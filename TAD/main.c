#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main(){

    int whileBreak = 0;
    Fila f = Iniializar();

    while(whileBreak == 0){
        printf("Escolha uma opcao: \n");
        printf("1 - Inserir um elemntto na fila \n");
        printf("2 - Remover um elemento da fila \n");
        printf("3 - Imprimir a fila \n");
        printf("4 - Sair \n");

        int opcao;
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("Qual elemnto quer inserir? \n");
            int elemento;
            scanf("%d", &elemento);
            Inserir(f, elemento);
            break;
        
        case 2:
            int removido;
            if(Remover(f, &removido))
                printf("Elemento %d removido com sucesso \n", removido);
            else
                printf("Fila vazia, nao foi possivel remover nenhum elemento \n");
            break;

        case 3:
            Imprimir(f);
            break;

        case 4:
            printf("Encerrando o programa... \n");
            whileBreak = 1;
            break;

        default:
            printf("Opcao invalida \n");
            break;
        }
    }
    f = Destruir(f);
    return 0;
}