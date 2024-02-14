#ifndef JOALHERIA_H
#define JOALHERIA_H
#include "bst.h"
#include "avl.h"
#include "rb.h"

//definindo os campos
typedef struct medicamento {
	int id;
	char nome[35];
 	int quantidade;
	int quilates;
	char material[35];
} produto;

typedef struct tabela {
	FILE *arquivo;
	arvoreBST arvoreBstIndice;
	arvoreAVL arvoreAvlIndice;
	arvoreRB arvoreRbIndice;
} tabela;

//Inicialização
int inicializarTabela(tabela *tab);
void finalizar (tabela *tab);
void adicionarProduto(tabela *tab, produto *p);
void removerProduto(tabela *tab, int id);

produto *ler_dados();
void tirar_enter(char *string);

//Procurar BST, AVL e RB
produto *procurarJoiasBST(tabela *tab, int chave);
produto	*procurarJoiasAvl(tabela* tab, int valor);
produto *procurarJoiasRB(tabela *tab, int chave); 
void buscarRb(int chave, arvoreRB raiz, tabela *tab);


//Imprimir BST, AVL e RB
void imprimirBst(arvoreBST raiz, tabela * tab);
void inOrderBst(arvoreBST raiz, tabela* tab);

void imprimirAvl(arvoreAVL raiz, tabela * tab);
void inOrderAvl(arvoreAVL raiz, tabela* tab);

void imprimirRb(arvoreRB raiz, tabela* tab);
void inOrderRb(arvoreRB raiz, tabela* tab);

//Salvar e Carregar, BST, AVL e RB
void salvarArquivoBst(char *nome, arvoreBST a);
void salvarAuxiliarBst(arvoreBST raiz, FILE *arq);
arvoreBST carregarArquivoBst(char *nome, arvoreBST a);

void salvarArquivoAvl(char *nome, arvoreAVL a);
void salvarAuxiliarAvl(arvoreAVL raiz, FILE *arq);
arvoreAVL carregarArquivoAvl(char *nome, arvoreAVL a);

void salvarArquivoRb(char *nome, arvoreRB a);
void salvarAuxiliarRb(arvoreRB raiz, FILE *arq);
arvoreRB carregarArquivoRb(char *nome, arvoreRB a);

#endif