#ifndef AVL_H
#define AVL_H
#include <stdio.h>

typedef struct indiceAVL {
    int chave;
    int indice; 
} indiceAVL;

typedef struct noAVL {
    indiceAVL *dado;
    int chave;
    int altura;
    struct noAVL *esquerdo, *direito;
} noAVL;

typedef noAVL *arvoreAVL;

void inicializar_avl(arvoreAVL *raiz);
int altura_avl(noAVL *noAVL);
int balanceamento_avl(arvoreAVL noAVL);
noAVL *minimo_avl(noAVL *novoNo);
int maior_avl(int num1, int num2);
arvoreAVL rotacaoSimplesDireitaAVL(arvoreAVL raiz);
arvoreAVL rotacaoSimplesEsquerdaAVL(arvoreAVL raiz);
arvoreAVL rotacaoDuplaDireitaAVL(arvoreAVL raiz);
arvoreAVL rotacaoDuplaEsquerdaAVL(arvoreAVL raiz);
arvoreAVL balancearAVL(arvoreAVL raiz);
arvoreAVL inserir_avl(indiceAVL *valor, arvoreAVL raiz);
void buscar_avl(arvoreAVL raiz, int elemento);
arvoreAVL remover_avl(arvoreAVL raiz, int valor);
void exibirEmOrdemAVL(arvoreAVL raiz);

#endif