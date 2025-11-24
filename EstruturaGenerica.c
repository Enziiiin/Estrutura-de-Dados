#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

typedef struct lista{
    void *info;
    struct lista *prox;
}Lista;

typedef struct pessoa{
    int tipo;  // 1 para aluno, 2 para professor
    void *info;
}Pessoa;

typedef struct aluno{
    int matricula;
    char nome[50];
    char curso[30];
}Aluno;

typedef struct professor{
    int matricula;
    char nome[50];
    int salario;
}Professor;

Lista *Inicializa(){
    return NULL;
}

void liberaLista(Lista **l){
    Lista *atual = *l;
    Lista *prox;

    while(atual != NULL){
        prox = atual->prox;
        free(atual->info);
        free(atual);
        atual = prox;
    }
    *l = NULL;
}

Lista* criaNo(void *info){
    Lista *no = malloc(sizeof(Lista));
    no->info = info;
    no->prox = NULL;
    return no;
}

void insereInicio(Lista **l, void *info){
    Lista *no = criaNo(info);
    no->prox = *l;
    *l = no;
}

Pessoa *criarPessoaAluno(int matricula, const char *nome, const char *curso){
    Pessoa *p = (Pessoa *)malloc(sizeof(Pessoa));
    Aluno *a = (Aluno *)malloc(sizeof(Aluno));
    a->matricula = matricula;
    strcpy(a->nome, nome);
    strcpy(a->curso, curso);
    p->tipo = 1; // Tipo 1 para aluno
    p->info = a;
    return p;
}

Pessoa *criarPessoaProfessor(int matricula, const char *nome, int salario){
    Pessoa *p = (Pessoa *)malloc(sizeof(Pessoa));
    Professor *prof = (Professor *)malloc(sizeof(Professor));
    prof->matricula = matricula;
    strcpy(prof->nome, nome);
    prof->salario = salario;
    p->tipo = 2; // Tipo 2 para professor
    p->info = prof;
    return p;
}

int removerPorMatricula(Lista **l, int matricula){
    Lista *atual = *l;
    Lista *anterior = NULL;
    while(atual != NULL){
        Pessoa *p = (Pessoa *)atual->info;
        if ( (p->tipo == 1 && ((Aluno *)p->info)->matricula == matricula)
          || (p->tipo == 2 && ((Professor *)p->info)->matricula == matricula) ) {
            if(p->tipo == 1){
                Aluno *a = (Aluno *)p->info;
                printf("Removendo Aluno - Matricula: %d, Nome: %s, Curso: %s\n", a->matricula, a->nome, a->curso);
            }
            else{
                Professor *pr = (Professor *)p->info;
                printf("Removendo Professor - Matricula: %d, Nome: %s, Salario: %d\n", pr->matricula, pr->nome, pr->salario);
            }
            if(anterior == NULL)
                *l = atual->prox;
            else
                anterior->prox = atual->prox;
            free(p->info);
            free(p); 
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Matricula %d nao encontrada na lista.\n", matricula);
    return 0;
}

int buscarPorMatricula(Lista *l, int matricula){
    Lista *atual = l;
    while(atual != NULL){
        Pessoa *p = (Pessoa *)atual->info;
        if(p->tipo == 1){
            Aluno *a = (Aluno *)p->info;
            if(a->matricula == matricula){
                printf("Aluno encontrado - Matricula: %d, Nome: %s, Curso: %s\n", a->matricula, a->nome, a->curso);
                return 1;
            }
        }
        else if(p->tipo == 2){
            Professor *pr = (Professor *)p->info;
            if(pr->matricula == matricula){
                printf("Professor encontrado - Matricula: %d, Nome: %s, Salario: %d\n", pr->matricula, pr->nome, pr->salario);
                return 1;
            }
        }
    }
    printf("Matricula %d nao encontrada \n", matricula);
    return 0;
}

int contarPorCursos(Lista *l, const char *curso){
    int cont = 0;
    for(; l; l = l->prox){
        Pessoa *p = (Pessoa*) l->info;
        if(p->tipo == 1){
            Aluno *a = (Aluno*) p->info;
            if(strcmp(a->curso, curso) == 0) 
                cont++;
        }
    }
    printf("Numero de alunos no curso %s: %d\n", curso, cont);
    return cont;
}

void imprimeMaiorSalario(Lista *l){
    int max = -1;
    for(Lista *it = l; it; it = it->prox){
        Pessoa *p = (Pessoa*) it->info;
        if(p->tipo == 2){
            Professor *pr = (Professor*) p->info;
            if(pr->salario > max) max = pr->salario;
        }
    }
    if(max < 0){
        printf("Nenhum professor cadastrado.\n");
        return;
    }
    printf("Salario maximo: %d\nProfessores com esse salario:\n", max);
    for(Lista *it = l; it; it = it->prox){
        Pessoa *p = (Pessoa*) it->info;
        if(p->tipo == 2){
            Professor *pr = (Professor*) p->info;
            if(pr->salario == max){
                printf("Matricula: %d, Nome: %s, Salario: %d\n", pr->matricula, pr->nome, pr->salario);
            }
        }
    }
}

int main(){

    int whileBreak = 0;
    Lista *listaPessoas = Inicializa();

    while(whileBreak == 0){
        printf("Escolha uma opção: \n");
        printf("1 - Inserir uma pessoa na lista\n");
        printf("2 - Remover um apessoa pela matricula\n");
        printf("3 - Buscar uma pessoa pela matricula\n");
        printf("4 - Contar o numero de alunos de um determinado curso\n");
        printf("5 - Imprimri os professores de maior salario\n");
        printf("6 - Sair\n");

        int opcao;
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("Qual tipo de pessoa deseja inserir? (1 - Aluno, 2 - Professor): ");
            int tipoPessoa;
            scanf("%d", &tipoPessoa);
            if(tipoPessoa == 1){
                int matricula;
                char nome[50];
                char curso[30];
                printf("\nDigite o nome do aluno: ");
                scanf(" %[^\n]", nome);
                printf("\nDigite a matricula do aluno: ");
                scanf("%d", &matricula);
                printf("\nDigite o curso do aluno: ");
                scanf(" %[^\n]", curso);
                Pessoa *p = criarPessoaAluno(matricula, nome, curso);
                insereInicio(&listaPessoas, p);
                printf("\nAluno inserido com sucesso!\n");
                
            } else if(tipoPessoa == 2){
                int matricula;
                char nome[50];
                int salario;
                printf("\nDigite o nome do professor: ");
                scanf(" %[^\n]", nome);
                printf("\nDigite a matricula do professor: ");
                scanf("%d", &matricula);
                printf("\nDigite o salario do professor: ");
                scanf("%d", &salario);
                Pessoa *p = criarPessoaProfessor(matricula, nome, salario);
                insereInicio(&listaPessoas, p);
                printf("\nProfessor inserido com sucesso!\n");
                
            } else {
                printf("\nTipo de pessoa inválido!\n");
            }
            break;
        
        case 2:
            printf("Digite a matricula da pessoa a ser removida: \n");
            int matRemov;
            scanf("%d", &matRemov);
            removerPorMatricula(&listaPessoas, matRemov);
            break;

        case 3:
            printf("Digite a matricula da pessoa a ser buscada: \n");
            int matBusca;
            scanf("%d", &matBusca);
            buscarPorMatricula(listaPessoas, matBusca);
            break;
        
        case 4:
            printf("Digite o nome do curso: \n");
            char cursoBusca[30];
            scanf(" %[^\n]", cursoBusca);
            contarPorCursos(listaPessoas, cursoBusca);
            break;
        
        case 5:
            imprimeMaiorSalario(listaPessoas);
            break;
        
        case 6:
            whileBreak = 1;
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida!\n");
            break;
        }
    }
    liberaLista(&listaPessoas);
    return 0;
}