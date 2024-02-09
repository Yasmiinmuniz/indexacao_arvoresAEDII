#ifndef TABELA_H
#define TABELA_H
#include "../arvores/bst.h"
#include "../arvores/bst.c"
#include "../arvores/rb.h"
#include "../arvores/rb.c"
#include "../arvores/avl.h"
#include "../arvores/avl.c"
#include <stdio_ext.h>

enum tipo_arvore {BST, AVL, RB};
typedef enum tipo_arvore tipo_arvore;

enum tipo_pokemon {BUG, DARK, DRAGON, ELETRIC, FAIRY,
				   FIGHTING, FIRE, FLYING, GHOST, GRASS,
				   GROUND, ICE, NORMAL, POISON, PSYCHIC,
				   ROCk, STEAL, WATER, UNDEFINED};
				   
typedef enum tipo_pokemon tipo_pokemon;

typedef struct pokemon {
	int removido;
	char nome[50];
	tipo_pokemon tipo[2];
	float altura;
	char* descricao;
	int codigo;
}dado;

typedef struct tabela {
	FILE *arquivo_dados;
	bst indiceBst;
	avl indice_avl;
	rb indice_rb;
} tabela;

int inicializarTabela(tabela *tab);

int inserir_pokemon(tabela *tab, dado *pok);
void remover_pokemon(tabela *tab, int indice);
dado buscar_pokemon(FILE *arq, int chave);

void salvar_pokemon(FILE *arq, dado *pok);
void imprimir_elemento(dado pok);
void listar_por_nome(FILE *arq, bst raiz);
void listar_por_codigo(FILE *arq, avl raiz);
void listar_por_descricao(FILE *arq, rb raiz);

void salvar_arquivoBst(char *nome, bst a);
void salvar_auxiliarBst(bst raiz, FILE *arq);

void salvar_arquivo_avl(char *nome, avl a);
void salvar_auxiliar_avl(avl raiz, FILE *arq);

void salvar_arquivo_rb(char *descricao, rb a);
void salvar_auxiliar_rb(rb raiz, FILE *arq);

void carregar_arquivo_arvore(tabela *tab, tipo_arvore tipo);

dado* ler_dados();
void tirar_enter(char *string);
void finalizar (tabela *tab);

#endif