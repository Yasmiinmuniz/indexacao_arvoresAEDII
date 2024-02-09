#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

No* menorNo(No* raiz) {
    No* atual = raiz;

    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }

    return atual;
}

No* inserir(Academia novaAcademia, No* raiz) {
    if (raiz == NULL) {
        No* novo = (No*)malloc(sizeof(No));
        novo->academia = novaAcademia;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    } else {
        int comparacao = novaAcademia.id - raiz->academia.id;

        if (comparacao < 0) {
            raiz->esquerda = inserir(novaAcademia, raiz->esquerda);
        } else if (comparacao > 0) {
            raiz->direita = inserir(novaAcademia, raiz->direita);
        }

        return raiz;
    }
}

void inordem(No* raiz) {
    if (raiz != NULL) {
        inordem(raiz->esquerda);
        printf("Nome: %s, ID: %d, RG: %s, Telefone: %s, Plano: %s\n",
               raiz->academia.nome, raiz->academia.id, raiz->academia.rg,
               raiz->academia.telefone, raiz->academia.plano);
        inordem(raiz->direita);
    }
}

Academia busca(int id, No* raiz) {
    if (raiz == NULL) {
        Academia vazia = {"", 0, "", "", ""};
        return vazia;
    }

    if (id < raiz->academia.id) {
        return busca(id, raiz->esquerda);
    } else if (id > raiz->academia.id) {
        return busca(id, raiz->direita);
    } else {
        return raiz->academia;
    }
}

No* remover(int id, No* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    if (id < raiz->academia.id) {
        raiz->esquerda = remover(id, raiz->esquerda);
    } else if (id > raiz->academia.id) {
        raiz->direita = remover(id, raiz->direita);
    } else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        No* temp = menorNo(raiz->direita);
        raiz->academia = temp->academia;
        raiz->direita = remover(temp->academia.id, raiz->direita);
    }

    return raiz;
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}
