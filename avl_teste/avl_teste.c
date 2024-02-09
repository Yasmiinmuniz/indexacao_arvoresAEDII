#include <stdlib.h>
#include <stdio.h>


typedef struct no
{
    int conteudo;
    struct no *esquerda, *direita;
    int altura;
    
} No;

No *criarNo(int valor){
    No *novo = malloc(sizeof(No));

    if(novo != NULL){
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    }
    else{
        printf("\nErro ao alocar o no!\n");
    }
    return novo;
}

int maior(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

int alturaNo(No *no){
    if(no == NULL){
        return -1;
    }
    else{
        return no->altura;
    }
}

int fatorBalanceamento(No *no){
    if(no != NULL){
        return (alturaNo(no->esquerda) - alturaNo(no->direita));
    }
    else{
        return 0;
    }
}

// Rotação Simples Esquerda
No *rotacaoEsquerda(No *raiz){
    No *aux, *filho;

    aux = raiz->direita;
    filho = aux->esquerda;

    aux->esquerda = raiz;
    raiz->direita = filho;

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    aux->altura = maior(alturaNo(aux->esquerda), alturaNo(aux->direita)) + 1;

    return aux;
}

// Rotação Simples Direita
No *rotacaoDireita(No *raiz){
    No *aux, *filho;

    aux = raiz->esquerda;
    filho = aux->direita;

    aux->direita = raiz;
    raiz->esquerda = filho;

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    aux->altura = maior(alturaNo(aux->esquerda), alturaNo(aux->direita)) + 1;
    
    return aux;
}

// Rotação Dupla Esquerda
No *rotacaoDireitaEsquerda(No *raiz){
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
}

// Rotação Dupla Direita
No *rotacaoEsquerdaDireita(No *raiz){
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
}

No *balancear(No *raiz){
    int fb = fatorBalanceamento(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->direita) <= 0){
        raiz = rotacaoEsquerda(raiz);
    }
    else if(fb > 1 && fatorBalanceamento(raiz->esquerda) >= 0){
        raiz = rotacaoDireita(raiz);
    }
    else if(fb > 1 && fatorBalanceamento(raiz->esquerda) < 0){
        raiz = rotacaoEsquerdaDireita(raiz);
    }
    else if(fb < -1 && fatorBalanceamento(raiz->direita) > 0){
        raiz = rotacaoDireitaEsquerda(raiz);
    }
    
    return raiz;
}

No *inserir(No *raiz, int valor){
    if(raiz == NULL){
        return criarNo(valor);
    }
    else{
        if(valor < raiz->conteudo){
            raiz->esquerda = inserir(raiz->esquerda, valor);
        }
        else if(valor > raiz->conteudo){
            raiz->direita = inserir(raiz->direita, valor);
        }
        else{
            printf("\nInsercao nao realizada! O elemento %d, ja existe", valor);
        }
    }
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

    raiz = balancear(raiz);
    
    return raiz;
}

No *remover(No *raiz, int chave){
    if(raiz == NULL){
        return NULL;
    }
    else{
        if(raiz->conteudo == chave){
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                printf("\nO valor %d, foi removido da arvore!\n", chave);
                return NULL;
            }
            else{
                if(raiz->esquerda != NULL && raiz->direita != NULL){
                    No *aux = raiz->esquerda;
                    while(aux->direita != NULL){
                        aux = aux->direita;
                    }
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerda = remover(raiz->esquerda, chave);
                }
                else{
                    No *aux;
                    if(raiz->esquerda != NULL){
                        aux = raiz->esquerda;
                    }
                    else{
                        aux = raiz->direita;
                    }
                    free(raiz);
                    printf("\nO valor %d, foi removido da arvore!", chave);
                    return aux;
                }
            }
        }
        else{
            if(chave < raiz->conteudo){
                raiz->esquerda = remover(raiz->esquerda, chave);
            }
            else{
                raiz->direita = remover(raiz->direita, chave);
            }
        }


        raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

        raiz = balancear(raiz);

        return raiz;
    }
}

void imprimir(No *raiz, int nivel){
    int i;
    if(raiz != NULL){
        imprimir(raiz->direita, nivel + 1);
        printf("\n\n");

        for(i = 0; i < nivel; i++)
            printf("\t");

        printf("[%d]", raiz->conteudo);
        imprimir(raiz->esquerda, nivel + 1);
    }
}

//main_avl.c

int main(){

    int opcao, valor;
    No *raiz = NULL;

    do{
        printf("\n1 - Inserir\n2 - Remover\n3 - Imprimir\n4 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("Informe o valor a ser inserido: ");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            printf("\n\n");
            imprimir(raiz, 1);
        
            break;
        case 2:
            printf("Informe o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 3:
            imprimir(raiz, 1);
            break;
        default:
            printf("\nOpcao invalida!\n");
        }

    }while(opcao != 4);
        printf("Saindo....");

    return 0;
}