#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função auxiliar que calcula a altura de um nó
int altura_avl(noAVL *noAVL) {
    if (noAVL == NULL) {
        return 0;
    }
    return noAVL->altura;
}

// Função para calcular o fator de balanceamento de um nó
int balanceamento_avl(arvoreAVL noAVL) {
    if(noAVL != NULL){
      
// Retorna a diferença entre a altura da subárvore esquerda e direita
        return (altura_avl(noAVL->esquerdo) - altura_avl(noAVL->direito));
    } else {
        return 0;
    }
}

// Esta função encontra o nó com o valor mínimo na árvore AVL
noAVL *minimo_avl(noAVL *noAVLvonoAVL) {
    noAVL *atual = noAVLvonoAVL;

    // Enquanto houver um filho esquerdo, percorre para a esquerda
    while (atual->esquerdo != NULL) {
        atual = atual->esquerdo;
    }

    return atual;
}

//Função auxiliar que calcula o maior valor entre dois números
int maior_avl(int num1, int num2) {
    int maior;
    if (num1 > num2) {
        maior = num1;
    } else {
        maior = num2;
    }
    return maior;
}

arvoreAVL rotacaoSimplesDireitaAVL(arvoreAVL raiz) {
    noAVL *aux = raiz->esquerdo;
    noAVL *temp = aux->direito;

    aux->direito = raiz;
    raiz->esquerdo = temp;

    raiz->altura = 1 + maior_avl(altura_avl(raiz->esquerdo), altura_avl(raiz->direito));
    aux->altura = 1 + maior_avl(altura_avl(aux->esquerdo), altura_avl(aux->direito));

    return aux;
}

arvoreAVL rotacaoSimplesEsquerdaAVL(arvoreAVL raiz) {
    noAVL *aux = raiz->direito;
    noAVL *temp = aux->esquerdo;

    temp->esquerdo = aux;
    raiz->direito = temp;

    aux->esquerdo = raiz;
    raiz->direito = temp;

    raiz->altura = maior_avl(altura_avl(raiz->esquerdo), altura_avl(raiz->direito)) + 1;
    aux->altura = maior_avl(altura_avl(aux->esquerdo), altura_avl(aux->direito)) + 1;

    return aux;
}

arvoreAVL rotacaoDuplaDireitaAVL(arvoreAVL raiz){
    raiz->esquerdo = rotacaoSimplesEsquerdaAVL(raiz->esquerdo);
    return rotacaoSimplesDireitaAVL(raiz);
}

arvoreAVL rotacaoDuplaEsquerdaAVL(arvoreAVL raiz){
    raiz->direito = rotacaoSimplesDireitaAVL(raiz->direito);
    return rotacaoSimplesEsquerdaAVL(raiz);
}

arvoreAVL balancearAVL(arvoreAVL raiz) {
    int fatorBalanceamento = balanceamento_avl(raiz);

    // Se o fator de balanceamento não for maior que -1 e menor que 1, a árvore está desbalanceada
    if (fatorBalanceamento > 1) {
        if (balanceamento_avl(raiz->esquerdo) >= 0) {
            // Rotação simples direita
            return rotacaoSimplesDireitaAVL(raiz);
        } else {
            // Rotação dupla direita (esquerda-direita)
            return rotacaoDuplaDireitaAVL(raiz);
        }
    } else if (fatorBalanceamento < -1) {
        if (balanceamento_avl(raiz->direito) <= 0) {
            // Rotação simples esquerda
            return rotacaoSimplesEsquerdaAVL(raiz);
        } else {
            // Rotação dupla esquerda (direita-esquerda)
            return rotacaoDuplaEsquerdaAVL(raiz);
        }
    }
  // Se o fator de balanceamento for maior que -1 e menor que 1, a árvore está balanceada
    return raiz;
}

// Inserir valor na árvore AVL
arvoreAVL inserir_avl(indiceAVL *valor, arvoreAVL raiz) {
    if (raiz == NULL) {
        arvoreAVL novo = (arvoreAVL)malloc(sizeof(noAVL));
        novo->dado = valor;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
        return novo;
    }else{
        if(valor->chave > raiz->dado->chave){
           raiz->direito = inserir_avl(valor, raiz->direito);
        } 
        else{
          raiz->esquerdo = inserir_avl(valor, raiz->esquerdo);
        }
    }

    raiz->altura = maior_avl(altura_avl(raiz->esquerdo), altura_avl(raiz->direito)) + 1;
    balancearAVL(raiz);

    return raiz;
}

void buscar_avl(arvoreAVL raiz, int elemento) {
    if (raiz == NULL) {
        printf("A Joia %d nao foi encontrada.\n", elemento);
        return;
    }

    if (raiz->chave == elemento) {
        printf("A Joia %d foi encontrada.\n", elemento);
        return;
    }

    if (elemento < raiz->chave) {
        buscar_avl(raiz->esquerdo, elemento);
    } else {
        buscar_avl(raiz->direito, elemento);
    }
}

arvoreAVL remover_avl(arvoreAVL raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    if (valor < raiz->chave) {
        raiz->esquerdo = remover_avl(raiz->esquerdo, valor);
    }
     
    else if (valor > raiz->chave) {
        raiz->direito = remover_avl(raiz->direito, valor);
    }

    else {
        if ((raiz->esquerdo == NULL) || (raiz->direito == NULL)) {
            noAVL *temp;
            if (raiz->esquerdo != NULL) {
                temp = raiz->esquerdo;
            } else {
                temp = raiz->direito;
            }

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else { 
                *raiz = *temp;
            }
            free(temp);
        } else {
            noAVL *temp = minimo_avl(raiz->direito);

            raiz->chave = temp->chave;

            raiz->direito = remover_avl(raiz->direito, temp->chave);
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->altura = 1 + maior_avl(altura_avl(raiz->esquerdo), altura_avl(raiz->direito));
    int fatorBalanceamento = balanceamento_avl(raiz);

    if (fatorBalanceamento > 1 && balanceamento_avl(raiz->esquerdo) >= 0) {
        return rotacaoSimplesDireitaAVL(raiz);
    }

    if (fatorBalanceamento < -1 && balanceamento_avl(raiz->direito) <= 0) {
        return rotacaoSimplesEsquerdaAVL(raiz);
    }

    if (fatorBalanceamento > 1 && balanceamento_avl(raiz->esquerdo) < 0) {
        return rotacaoDuplaDireitaAVL(raiz);
    }

    if (fatorBalanceamento < -1 && balanceamento_avl(raiz->direito) > 0) {
        return rotacaoDuplaEsquerdaAVL(raiz);
    }

    return raiz;
}

void exibirEmOrdemAVL(arvoreAVL raiz) {
    if (raiz != NULL) {
        exibirEmOrdemAVL(raiz->esquerdo);
        printf("%d ", raiz->dado);
        exibirEmOrdemAVL(raiz->direito);
    }
}