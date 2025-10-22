#include <stdlib.h>
#include <stdio.h>

typedef struct arvore{
    int valor;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

arvore *LerArvore(FILE *arq){
    char c;
    int num;

    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &num);

    if(num == -1){
        fscanf(arq, "%c", &c);
        return NULL;
    }else{
        arvore *a = (arvore *)malloc(sizeof(arvore));
        a->valor = num;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq, "%c", &c);
        return a;
    }
};

int altura (arvore *a){
    if(a==NULL)
        return 0;
    else{
        int he= altura(a->esq);
        int hd= altura(a->dir);
        if (he>hd)
            return he+1;
        else
            return hd+1;
    }
};

void ImprimirPre(arvore *a){
    if(a != NULL){
        printf("%d ", a->valor);
        ImprimirPre(a->esq);
        ImprimirPre(a->dir);
    }
};

void ImprimirEm(arvore *a){
    if(a != NULL){
        ImprimirPre(a->esq);
        printf("%d ", a->valor);
        ImprimirPre(a->dir);
    }
};

void ImprimirPos(arvore *a){
    if(a != NULL){
        ImprimirPre(a->esq);
        ImprimirPre(a->dir);
        printf("%d ", a->valor);
    }
};


void ImprimirNivel(arvore *a,int cont,int nivel){
    if(a!=NULL){
        if(cont == nivel)
        printf("%d ", a->valor);
        else{
            ImprimirNivel(a->esq, cont+1, nivel);
            ImprimirNivel(a->dir, cont+1, nivel);
        }
    }
};

void ImprimirLargura(arvore *a){
    int h = altura(a);
    for (int i = 0; i < h; i++) {
        ImprimirNivel(a, 0, i);
        printf("\n");
    }
};

int Contar(arvore *a){
    if(a ==NULL)
        return 0;
    else
        return 1 + Contar(a->esq) + Contar(a->dir);
};

void ImprimirFolhas(arvore *a){
    if(a != NULL){
        if(a->esq == NULL && a->dir == NULL)
            printf("%d ", a->valor);
        ImprimirFolhas(a->esq);
        ImprimirFolhas(a->dir);
    }
};

int Existe(arvore *a, int x){
    if(a == NULL)
        return 0;
    if(a->valor == x)
        return 1;
    else
        return Existe(a->esq, x) || Existe(a->dir, x);
};

int Ordenada(arvore *a){
    if(a == NULL)
        return 1;
    if(a->esq != NULL && a->esq->valor > a->valor)
        return 0;
    if(a->dir != NULL && a->dir->valor < a->valor)
        return 0;
    if(!Ordenada(a->esq) || !Ordenada(a->dir))
        return 0;
    return 1;
};

int Cheia(arvore *a){
    int h = altura(a);
    int total = Contar(a);
    return total == (1 << h) - 1;
};

int NivelNo(arvore *a, int x, int nivel_atual) {
    if (a == NULL)
        return -1;

    if (a->valor == x)
        return nivel_atual;

    int esq = NivelNo(a->esq, x, nivel_atual + 1);
    if (esq != -1) return esq;

    return NivelNo(a->dir, x, nivel_atual + 1);
};

int main(){

    FILE *arq;
    arvore *a = NULL;

    int opcao;
    int WhileBreak = 0;
    char arquivo[100];

    while(WhileBreak == 0){

        printf("\nEscolha uma das opcoes abaixo: \n");
        printf("1 - Ler a arvore\n");
        printf("2 - Imprimir a arvore\n");
        printf("3 - Verificar se um elemento X existe na arvore\n");
        printf("4 - Contar o numero de elementos da arvore\n");
        printf("5 - Imprimir os nos folhas da arvore\n");
        printf("6 - Verificar se a arvore esta ordenada\n");
        printf("7 - Verificar se a arvore esta completa\n");
        printf("8 - Imprimir o nivel a qual o no X pertence\n");
        printf("9 - Sair\n\n");

        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("Digite o nome do arquivo:\n");
            scanf("%s", arquivo);
            arq = fopen(arquivo, "r");
            if (arq == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                break;
            }

            a = LerArvore(arq);
            fclose(arq);
            printf("Arvore carregada com sucesso!\n");
            break;
            
        case 2:
            printf("Escolha o tipo de impressao:\n");
            printf("1 - Pre-ordem\n");
            printf("2 - Em-ordem\n");
            printf("3 - Pos-ordem\n");
            printf("4 - Em Largura\n");
            int tipo;
            scanf("%d", &tipo);
            switch(tipo){
                case 1:
                    ImprimirPre(a);
                    break;
                case 2:
                    ImprimirEm(a);
                    break;
                case 3:
                    ImprimirPos(a);
                    break;
                case 4:
                    ImprimirLargura(a);
                    break;
                default:
                    printf("Tipo invalido!\n");
                    break;
            }
            printf("\n");
            break;
        
        case 3:
            printf("Digite o valor de X:\n");
            int x;
            scanf("%d", &x);
            if(Existe(a, x) == 1)
                printf("O elemento %d existe na arvore.\n", x);
            else
                printf("O elemento %d nao existe na arvore.\n", x);
            break;
        
        case 4:
            printf("A arvore possui %d elementos\n", Contar(a));
            break;

        case 5:
            printf("Nos folhas da arvore: ");
            ImprimirFolhas(a);
            break;

        case 6:
            if(Ordenada(a) == 1)
                printf("A arvore esta ordenada\n");
            else
                printf("A arvore nao esta ordenada\n");
            break;

        case 7: 
            if(Cheia(a) == 1)
                printf("A arvore esta completa\n");
            else
                printf("A arvore nao esta completa\n");
            break;

        case 8:
            printf("Digite o valor do no que deseja saber o nivel:\n");
                scanf("%d", &x);
                int nivel = NivelNo(a, x, 0);
                if (nivel != -1)
                    printf("O no %d esta no nivel %d\n", x, nivel);
                else
                    printf("O no %d nao foi encontrado na arvore\n", x);
            break;

        case 9:
            printf("Encerrando o programa...\n");
            WhileBreak = 1;
            break;
        }    
    }
    return 0;
}