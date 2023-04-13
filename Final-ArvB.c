#include <stdio.h>
#include <stdlib.h>

//Warning: windons code - "system("cls")"

typedef struct disciplina{
    int id;
    char *nome;
    double notaFinal;
}DI;

typedef struct no{
    int count;
    int chave;
    int idade;
    char *nome;
    DI *disciplinas[5];
    struct no *esq;
    struct no *dir;
}NO;

NO* raiz = NULL;

NO* busca(int x, NO* aux){
    if(aux == NULL){
        return NULL; 
    }else if(x == aux->chave){
        return aux; 
    }else if(x<aux->chave){ 
        if(aux->esq != NULL){
            return busca(x, aux->esq);
        }else{
            return aux; 
        }
    }else{
        if(aux->dir != NULL){
            return busca(x, aux->dir);
        }else{//dir esta vazia
            return aux; 
        }
    }
}

void add(int chave, char *nomeAluno, int idade){
    NO* resp = busca(chave, raiz);
    if(resp == NULL || resp->chave != chave){
        NO* novo = malloc(sizeof(NO));
        novo->chave = chave;
        novo->nome = nomeAluno;
        novo->idade = idade;
        novo->count = 0; 
        novo->esq = NULL;
        novo->dir = NULL;
        
        if(resp == NULL){ 
            raiz = novo;
        }else{
            if(chave < resp->chave){
                resp->esq = novo;
            }else{
                resp->dir = novo;
            }
        }
    }else{
        printf("Add invalida. Chave duplicada");
    }
}

void add_disciplinas(int matricula, int codigo, char *nome, float nota){
    NO *aluno = busca(matricula, raiz);
    if(aluno == NULL || aluno->chave != matricula){
        printf("Aluno nao encontrado\n");
    }
    if(aluno->count<5){
        DI *novo = malloc(sizeof(DI));
        novo->id = codigo;
        novo->nome =  nome;
        novo->notaFinal = nota;
        aluno->disciplinas[aluno->count] = novo;
        aluno->count++;
    }
}

void alterar(int matricula){
    NO* aux = busca(matricula, raiz);
    int escolha;
    printf("O que deseja alterar?\n[1] - Idade\n[2] - Nome\nEscolher: ");
    scanf("%d", &escolha);
    if(escolha == 1){
        printf("Digite a nova idade: ");
        scanf("%d", &aux->idade);
    }else if(escolha == 2){
        //Maior problema do Codigo:
        printf("Digite o novo nome: ");
        aux->nome = malloc (sizeof(char)*100);
        scanf("%s", aux->nome);
        printf("Alteracao concluida \n");
    }else{
        printf("Opção Invalida.");
    }
}

NO* remover(NO *raiz, int chave){
    if(raiz == NULL){ 
        printf("Aluno nao encontrado\n");
        return 0;
    }   
    else{ 
        if(raiz->chave == chave){ 
            if(raiz->esq == NULL && raiz->dir == NULL){  
                free(raiz);
                return NULL; 
            }else{ 
                if(raiz->dir == NULL || raiz->esq == NULL){
                    NO *aux;
                    if(raiz->esq != NULL){     
                        aux = raiz->esq;       
                    }else{                          
                        aux = raiz->dir;
                    }
                    free(raiz);  
                    return aux;  
                }else{
                    NO *aux = raiz->esq;
                    while(aux->dir != NULL){
                        aux = aux->dir;
                    }
                    raiz->chave = aux->chave;
                    aux->chave = chave;   
                    raiz->esq = remover(raiz->esq, chave);  
                    return raiz;
                }
            }
        }
        else{ 
            if(chave < raiz->chave){ 
                raiz->esq = remover(raiz->esq, chave);  
            }else{
                raiz->dir = remover(raiz->dir, chave);
            }
            return raiz;
        }
    }
}

void buscarAluno(int matricula){
    DI *aux2;
    NO* aux = busca(matricula, raiz);
    if(aux == NULL || aux->chave != matricula){
        printf("Aluno nao encontrado.\n");
        return;
    }
    ordenar(matricula);
    printf("Nome: %s\n", aux->nome);
    printf("Idade: %d\n", aux->idade);

    for(int i = 0; i < aux->count; i++){
        aux2 = aux->disciplinas[i];
        printf("Disciplina %d:\n", i + 1);
        printf("Codigo: %d\n", aux2->id);
        printf("Nome: %s\n", aux2->nome);
        printf("Nota Final: %.2f\n", aux2->notaFinal);
    }
}

void ordenar(int matricula){
    DI *aux2;
    NO* aux = busca(matricula, raiz);
    if(aux == NULL || aux->chave != matricula){
        printf("\nAluno nao encontrado\n");
        return;
    }
    for (int i = 0; i < aux->count; i++) {
        float maior = aux->disciplinas[i]->notaFinal;
        int pos = i;

        for (int j = i; j < aux->count; j++) {
            if (maior < aux->disciplinas[j]->notaFinal){
                maior = aux->disciplinas[j]->notaFinal;
                pos = j;
            }
        }  
        aux2 = aux->disciplinas[i];
        aux->disciplinas[i] = aux->disciplinas[pos];
        aux->disciplinas[pos] = aux2;
    }
}

void imprimirInOrdem(NO *raiz){
    if(raiz != NULL){
        imprimirInOrdem(raiz->esq);
        printf("[%s]     ", raiz->nome);     
        printf("[%d]     ", raiz->chave);   
        printf("[%d]   \n", raiz->idade);
        imprimirInOrdem(raiz->dir);       
    }
}
    
int main(){
    int opcao, matricula, idade, choose, quant, codigo;
    float nota;
    char *nome, *nomeDis;

    add(1, "Vitor", 20);

    system("cls");

    do{
        printf("====================\n Binary Tree School\n====================\n[1] - Adicionar\n[2] - Remover\n[3] - Alterar\n[4] - Buscar\n[5] - Imprimir\nEscolha: ");
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            nome = malloc(sizeof(char)*100);
            printf("Nova Matricula: ");
            scanf("%d", &matricula);
            printf("Nome do Aluno: ");
            scanf("%s", nome);
            printf("Idade: ");
            scanf("%d", &idade);
            add(matricula, nome, idade);
            printf("[*] Aluno Adicinado!\n");
            _sleep(1000);
            printf("Deseja adicionar disciplinas do aluno?\n[1] - Sim\n[2] - Nao\nEscolha: ");
            scanf("%d", &choose);
            if(choose == 1){
                printf("Quantas deseja adicionar: ");
                scanf("%d", &quant);
                for(int i = 0; i < quant; i++){
                    printf("---------------------\n");
                    nomeDis = malloc(sizeof(char)*100);
                    printf("Nome da disciplina: ");
                    scanf("%s", nomeDis);
                    printf("Codigo da disciplina: ");
                    scanf("%d", &codigo);
                    printf("Nota Final: ");
                    scanf("%f", &nota);
                    add_disciplinas(matricula, codigo, nomeDis, nota);
                }
                printf("[*] Tudo Feito!\n");
            }else{
                system("cls");
            }
            break;
        case 2:
            printf("Matricula do Aluno: ");
            scanf("%d", &matricula);
            raiz = remover(raiz, matricula);
            printf("Operação concluida !");
            _sleep(1000);
            system("cls");
            break;
        case 3:
            printf("Matricula do Aluno: ");
            scanf("%d", &matricula);
            alterar(matricula);
            _sleep(1000);
            system("cls");
            break;
        case 4:
            printf("Matricula do Aluno: ");
            scanf("%d", &matricula);
            buscarAluno(matricula);
            break; 
        case 5:
            imprimirInOrdem(raiz);
            break;
        default:
            printf("Opcao Invalida\n");
        }
    }while(opcao != 5);
    return 0;
}