#ifndef BST_H
#define BST_H
#include <stdlib.h>

typedef struct indiceBst {
	char* nome;
	int indice; //posição em bytes do primeiro byte do registro no arquivo de dados
}indiceBst;

typedef struct no_bst {
	indiceBst *dado;
	struct no_bst *esq, *dir;
} no_bst;

typedef no_bst * bst;

indiceBst* inicializarIndiceBst(int indice, char* nome);
bst adicionarBst(indiceBst *valor, bst raiz);
int altura(bst raiz);
int maior(int a, int b);
indiceBst * maior_elemento_bst(bst raiz);
indiceBst * menor_elemento_bst(bst raiz);
void pre_order_bst(bst raiz);
void pos_order_bst(bst raiz);
void in_order_bst(bst raiz);
bst remover_bst(bst raiz, char* nome);
void imprimir_elemento_bst(bst raiz);
int buscaIndiceBst(bst raiz, char* nome);

#endif
