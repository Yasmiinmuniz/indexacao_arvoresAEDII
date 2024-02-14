#ifndef BST_H
#define BST_H

typedef struct indiceBST {
	int chave;
	int indice;
} indiceBST;

typedef struct noBST {
    indiceBST *dado;
    struct noBST *esq;
    struct noBST *dir;
} noBST;

typedef noBST *arvoreBST;

arvoreBST inserirBST(arvoreBST raiz, indiceBST *valor);
void preorderBST(arvoreBST raiz);
void inorderBST(arvoreBST raiz);
void posorderBST(arvoreBST raiz);
indiceBST *maiorElementoBST(arvoreBST raiz);
arvoreBST removerBST(arvoreBST raiz, int valor);
int buscaBST(arvoreBST raiz, indiceBST *valor);
int alturaBST(arvoreBST raiz);

#endif