#ifndef RB_H
#define RB_H

enum COR {VERMELHO, PRETO};

typedef struct indiceRB {
	int chave;
	int indice;
} indiceRB;

typedef struct noRB {
    enum COR cor;
    indiceRB *dado;
    struct noRB *esquerdo, *direito, *pai;
    int altura;
}noRB;

typedef noRB *arvoreRB;


void inicializarRB(arvoreRB *raiz);
arvoreRB criarNoRB(indiceRB *valor);
void preOrderRB(arvoreRB raiz);
int corRB(arvoreRB no);
int ehEsquerdoRB(arvoreRB no);
int ehRaizRB(arvoreRB no);
arvoreRB tioRB(arvoreRB n);
void rotacaoSimplesDireitaRB(arvoreRB* raiz, arvoreRB no, int simples);
void rotacaoSimplesEsquerdaRB(arvoreRB* raiz, arvoreRB no, int simples);
void rotacaoDuplaDireitaRB(arvoreRB* raiz, arvoreRB no);
void rotacaoDuplaEsquerdaRB(arvoreRB* raiz, arvoreRB no);
void ajustarRB(arvoreRB* raiz, arvoreRB no);
void inserirRB(indiceRB *valor, arvoreRB* raiz);
void ajustarRemocaoRB(arvoreRB* raiz, arvoreRB filho, arvoreRB pai);
void removerRB(arvoreRB* raiz, int chave);
arvoreRB buscarRB(arvoreRB raiz, int chave);

#endif