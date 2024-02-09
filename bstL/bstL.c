#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstL.h"

indiceBst* inicializarIndiceBst(int indice, char* nome)  {
	indiceBst *novo = (indiceBst*) malloc(sizeof(indiceBst));
	novo->indice = indice;
	novo->nome = (char *) malloc(sizeof(nome));
	strcpy(novo->nome, nome);
	return novo;
}

bst adicionarBst(indiceBst *valor, bst raiz) {
    if(raiz == NULL) {
		bst novo = (bst) malloc(sizeof(struct no_bst));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}

	if(strcmp(valor->nome, raiz->dado->nome) > 0) {
		raiz->dir = adicionarBst(valor, raiz->dir);
	} else {
		raiz->esq = adicionarBst(valor, raiz->esq);
	}
	return raiz;
}

bst remover_bst(bst raiz, char* nome) {
  if (raiz == NULL)
    return raiz;

  if (strcmp(raiz->dado->nome, nome) == 0) {
      if (raiz->dir == NULL && raiz->esq == NULL) {
			free(raiz->dado);
	    	free (raiz);
	    	return NULL;
	    }
      if (raiz->dir == NULL && raiz->esq != NULL) {
		bst aux = raiz->esq;
		free (raiz);
		return aux;
      }
      if (raiz->esq == NULL && raiz->dir != NULL) {
        bst aux = raiz->dir;
        free (raiz);
        return aux;
      }
      raiz->dado = maior_elemento_bst(raiz->esq);
      raiz->esq = remover_bst(raiz->esq, raiz->dado->nome);
  } else {
	if (strcmp(nome, raiz->dado->nome) > 0)
    	raiz->dir = remover_bst(raiz->dir, nome);
	else
		raiz->esq = remover_bst(raiz->esq, nome);
  }
  return raiz;
}

int altura_bst(bst raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura_bst(raiz->dir), altura_bst(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

indiceBst* maior_elemento_bst(bst raiz) {
	if(raiz == NULL)
		return NULL;
	if(raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento_bst(raiz->dir);
}

indiceBst* menor_elemento_bst(bst raiz) {
	if(raiz == NULL)
		return NULL;
	if(raiz->esq == NULL)
		return raiz->dado;
	else
		return menor_elemento_bst(raiz->esq);
}

void pre_order_bst(bst raiz) {
	if(raiz != NULL) {
		imprimir_elemento_bst(raiz);
		pre_order_bst(raiz->esq);
		pre_order_bst(raiz->dir);
	}
}

void pos_order_bst(bst raiz) {
	if(raiz != NULL) {
		pos_order_bst(raiz->esq);
		pos_order_bst(raiz->dir);
		imprimir_elemento_bst(raiz);
	}
}

void in_order_bst(bst raiz) {
	if(raiz != NULL) {
		in_order_bst(raiz->esq);
		imprimir_elemento_bst(raiz);
		in_order_bst(raiz->dir);
	}
}

void imprimir_elemento_bst(bst raiz) {
	if(raiz != NULL) {
		printf("%s | ", raiz->dado->nome);

	}
}

int buscaIndiceBst(bst raiz, char* nome) {
	if(nome != NULL && raiz != NULL) {
		int cmp = strcmp(nome, raiz->dado->nome);
		if(cmp == 0) {
			return raiz->dado->indice;
		}
		else {
			if(cmp > 0)
				return buscaIndiceBst(raiz->dir, nome);
			else 
				return buscaIndiceBst(raiz->esq, nome);
		}
	} else {
		return -1;
	}
}
