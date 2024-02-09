#ifndef BST_H
#define BST_H

typedef struct Academia {
    char nome[50];
    int id;
    char rg[15];
    char telefone[15];
    char plano[20];
} Academia;

typedef struct No {
    Academia academia;
    struct No* esquerda;
    struct No* direita;
} No;

No* menorNo(No* raiz);
No* inserir(Academia novaAcademia, No* raiz);
void inordem(No* raiz);
Academia busca(int id, No* raiz);
No* remover(int id, No* raiz);
void liberarArvore(No* raiz);

#endif
