#include <stdlib.h>
#include <stdio.h>

// Considerando que a arvore lida e uma ABB

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

int Existe(arvore *a, int x){
    if(a == NULL)
        return 0;
    if(a->valor == x)
        return 1;
    else
        return Existe(a->esq, x) || Existe(a->dir, x);
};

void ImprimirFolhas(arvore *a){
    if(a != NULL){
        if(a->esq == NULL && a->dir == NULL)
            printf("%d ", a->valor);
        ImprimirFolhas(a->esq);
        ImprimirFolhas(a->dir);
    }
};

void ImprimirFolhasMenores(arvore *a, int x){
    if(a != NULL){
        if(a->esq == NULL && a->dir == NULL && a->valor < x)
            printf("%d ", a-> valor);
        ImprimirFolhasMenores(a->esq, x);
        ImprimirFolhasMenores(a->dir, x);
    }
}

int NivelNo(arvore *a, int x, int nivel_atual) {
    if(a == NULL)
        return -1;

    if(a->valor == x)
        return nivel_atual;

    if(x < a->valor)
        return NivelNo(a->esq, x, nivel_atual + 1);
    else
        return NivelNo(a->dir, x, nivel_atual + 1);
};

arvore *Inserir(arvore *a, int x){
    if(a == NULL){
        arvore *novo = (arvore *)malloc(sizeof(arvore));
        novo->valor = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    else{
        if(x <= a->valor)
            a->esq = Inserir(a->esq, x);
        else
            a->dir = Inserir(a->dir, x);
        return a;
    }
}

arvore *remover(arvore *a, int x){
    if(a == NULL)
        return NULL;
    if(x < a->valor){
        a->esq = remover(a->esq, x);
    }else if(x > a->valor){
        a->dir = remover(a->dir, x);
    }else{
        if(a->esq == NULL && a->dir == NULL){
            free(a);
            return NULL;
        }else if(a->esq == NULL){
            arvore *temp = a->dir;
            free(a);
            return temp;
        }else if(a->dir == NULL){
            arvore *temp = a->esq;
            free(a);
            return temp;
        }else{
            arvore *temp = a->dir;
            while(temp->esq != NULL){
                temp = temp->esq;
            }
            a->valor = temp->valor;
            a->dir = remover(a->dir, temp->valor);
        }
    }
    return a;
}

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
        printf("4 - Imprimir o nivel de um no X\n");
        printf("5 - Imprimir as folhas menores que um valor X\n");
        printf("6 - Inserir um no X na arvore\n");
        printf("7 - Remover um no X na arvore\n");
        printf("8 - Sair\n\n");

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
            printf("Digite um valor que voce quer saber o nivel\n");
            int y;
            scanf("%d", &y);
            if(NivelNo(a, y, 0) != -1)
                printf("O nivel do no %d e: %d\n", y, NivelNo(a, y, 0));
            else
                printf("O no %d nao existe na arvore\n", y);

            break;

        case 5:
            printf("Digite o valor que voce quer saber as folhas menores\n");
            int z;
            scanf("%d", &z);
            printf("Nos folhas menores que %d: ", z);
            ImprimirFolhasMenores(a, z);
            break;

        case 6:
            printf("Digite o valor que deseja inserir\n");
            int w; 
            scanf("%d", &w);
            a = Inserir(a, w);
            break;    

        case 7: 
            printf("Digite o valor que deseja remover\n");
            int v;
            scanf("%d", &v);
            a = remover(a, v);
            break;

        case 8:
            printf("Encerrando o programa...\n");
            WhileBreak = 1;
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }    
    }
    return 0;
}