#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

// Recebe um valor e um nó da árvore e retorna o nó da árvore resultante da inserção do valor
arvoreBST inserirBST(arvoreBST raiz, indiceBST *valor){
    if (raiz == NULL){
        arvoreBST novo = (arvoreBST)malloc(sizeof(struct noBST));
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (raiz->dado->chave < valor->chave)
    {
       raiz->dir = inserirBST(raiz->dir, valor);
    }else{
      raiz->esq = inserirBST( raiz->esq, valor);
    }
    return raiz;
}

//Recebe como parâmetro o ponteiro para uma árvore BST e imprime seus elementos, seguindo a pré-ordem, 
void preorderBST(arvoreBST raiz) {
    if(raiz != NULL) {
        printf("[%d]", raiz->dado);
        preorderBST(raiz->esq);
        preorderBST(raiz->dir);
    }
}

//Recebe como parâmetro o ponteiro para uma árvore BST e imprime na tela todos seus elementos, seguindo a ordem in-order.
// void inorderBST(arvoreBST raiz){
//     if(raiz != NULL) {
//         inorderBST(raiz->esq);
//         printf("[%d]", raiz->dado \n);
//         inorderBST(raiz->dir);
//     }
//}

//Recebe como parâmetro o ponteiro para uma árvore BST e imprime na tela todos seus elementos, seguindo a ordem pós-order.
void posorderBST(arvoreBST raiz) {
    if(raiz != NULL) {
        posorderBST(raiz->esq);
        posorderBST(raiz->dir);
        printf("[%d]", raiz->dado);
    }
}

indiceBST *maiorElementoBST(arvoreBST raiz) {
	if(raiz == NULL) {
		return NULL;
    } if(raiz->dir == NULL) {
		return raiz->dado;
    } else{
		return maiorElementoBST(raiz->dir);
    }
}

//Recebe como parâmetros um número inteiro e o ponteiro para raiz de uma árvore BST, retorna o ponteiro para árvore após a remoção do valor passado como primeiro parâmetro
arvoreBST removerBST(arvoreBST raiz, int valor) {
    if(raiz == NULL){ 
		return NULL;
	}
	
	else if(raiz->dado->chave == valor) {		
		if(raiz->esq == NULL) {
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}
		raiz->dado = maiorElementoBST(raiz->esq);
		raiz->esq = removerBST(raiz->esq, raiz->dado->chave);
		return raiz;
	}	
	else if(valor > raiz->dado->chave) {
			raiz->dir = removerBST(raiz->dir, valor);
	} else {
			raiz->esq = removerBST(raiz->esq, valor);
	}
	return raiz;
}

//Recebe como parâmetro o ponteiro para uma árvore BST e o valor de uma chave de procura. A função deve retornar o valor 1, caso a chave exista na árvore e 0 em caso contrário.
int buscaBST(arvoreBST raiz, indiceBST *valor) {
    if (raiz == NULL) {
        return 0;
    }

    if (raiz->dado == valor) {
        return 1;
    }

    if (raiz->dado > valor) {
        return buscaBST(raiz->esq, valor);
    } else {
        return buscaBST(raiz->dir, valor);
    }
}


//Recebe como parâmetro o ponteiro para uma árvore BST e retorna a altura da árvore.
int alturaBST(arvoreBST raiz) {
    if (raiz == NULL) {
        return -1; 
    } else {
        int alturaEsq = alturaBST(raiz->esq);
        int alturaDir = alturaBST(raiz->dir);

        if (alturaEsq > alturaDir) {
            return alturaEsq + 1;
        } else {
            return alturaDir + 1;
        }
    }
}