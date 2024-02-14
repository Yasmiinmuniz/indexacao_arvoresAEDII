#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joalheria.h"

void inicializarBST(arvoreBST *raiz){
  *raiz = NULL;
}

void inicializarAVL(arvoreAVL *raiz){
  *raiz = NULL;
}

void inicializarRB(arvoreRB *raiz){
  *raiz = NULL;
}

// ARQUIVOS
int inicializarTabela(tabela *tab){
  inicializarBST(&tab->arvoreBstIndice);
  inicializarAVL(&tab->arvoreAvlIndice);
  inicializarRB(&tab->arvoreRbIndice);
  tab->arquivo = fopen("dados.dat", "a+b");
  tab->arvoreBstIndice = carregarArquivoBst("indicesBST.dat", tab->arvoreBstIndice);
  tab->arvoreAvlIndice = carregarArquivoAvl("indicesAVL.dat", tab->arvoreAvlIndice);
  tab->arvoreRbIndice = carregarArquivoRb("indicesRB.dat", tab->arvoreRbIndice);

  if(tab->arquivo != NULL)
    return 1;
  else
    return 0;
}

void finalizar (tabela *tab) {
  fclose(tab->arquivo);
  salvarArquivoBst("indicesBST.dat", tab->arvoreBstIndice);
  salvarArquivoAvl("indicesAVL.dat", tab->arvoreAvlIndice);
  salvarArquivoRb("indicesRB.dat", tab->arvoreRbIndice);
}

void adicionarProduto(tabela *tab, produto *p){
  int posicaoNovoRegistro;

  if(tab->arquivo != NULL) {
      fseek(tab->arquivo, 0L, SEEK_END);
      posicaoNovoRegistro = ftell(tab->arquivo);

      // Adicionar BST - ID
      indiceBST *novo = (indiceBST*)malloc(sizeof(indiceBST));
      novo->chave = p->id;
      novo->indice = posicaoNovoRegistro;
      tab->arvoreBstIndice = inserirBST(tab->arvoreBstIndice, novo);

      // Adicionar AVL - Quilates
      indiceAVL *aux = (indiceAVL*)malloc(sizeof(indiceAVL));
      aux->chave = p->quilates;
      aux->indice = posicaoNovoRegistro;
      tab->arvoreAvlIndice = inserir_avl(aux, tab->arvoreAvlIndice);

      // Adicionar RB - Quantidade
      indiceRB *auxRB = (indiceRB*)malloc(sizeof(indiceRB));
      auxRB->chave = p->quantidade;
      auxRB->indice = posicaoNovoRegistro;
      inserirRB(auxRB,&tab->arvoreRbIndice);

      fwrite(p, sizeof(produto), 1, tab->arquivo);
  }
}

void removerProduto(tabela *tab, int id){
  produto *p = procurarJoiasBST(tab, id);	
  if(p == NULL){
    return;
  }else{
    tab->arvoreBstIndice = removerBST(tab->arvoreBstIndice, p->id);
    tab->arvoreAvlIndice = remover_avl(tab->arvoreAvlIndice, p->quilates);
    removerRB(&tab->arvoreRbIndice, p->quantidade);
  }
}

produto *ler_dados() {
  produto *novo = (produto*) malloc(sizeof(produto));
  char * buffer = (char *) malloc(256*sizeof(char));

  system("clear");
  printf("------------------------------------\n");
  printf("              JOALHERIA             \n");
  printf("------------------------------------\n");
  getchar();

  printf("Nome: ");
  fgets(novo->nome, 20,  stdin);
  tirar_enter(novo->nome);

    printf("------------------------------------\n");

  printf("Quantidade: ");
  scanf("%d", &novo->quantidade);

    printf("------------------------------------\n");


  printf("Quilates: ");
  scanf("%d", &novo->quilates);

    printf("------------------------------------\n");

  printf("Material: ");
  fgets(novo->material, 20,  stdin); 
  fgets(novo->material, 20,  stdin); 
  tirar_enter(novo->material);

    printf("------------------------------------\n");

  printf("ID: ");
  scanf("%d", &novo->id);

    printf("------------------------------------\n");

    free(buffer);
  return novo;
}

void tirar_enter(char *string) {
  string[strlen(string) -1] = '\0';
}

// ------------ B S T ------------ 

produto *procurarJoiasBST(tabela *tab, int chave) {
    if(tab->arquivo != NULL) {
    noBST *temp;
    temp = tab->arvoreBstIndice;
    while(temp!=NULL){
        if(temp->dado->chave == chave) {

    fseek(tab->arquivo, temp->dado->indice, SEEK_SET);

    produto * encontrado = (produto*) malloc(sizeof(produto));
    fread(encontrado, sizeof(produto), 1, tab->arquivo);

    int tam;
    fread(&tam, sizeof(int),1, tab->arquivo);
    fread(encontrado->nome, sizeof(char), tam, tab->arquivo);

    printf("----------------------------------------------------------------\n");
    printf("ID: %d, Nome: %s, Quantidade: %d, Quilates: %d, Material: %s\n", encontrado->id, encontrado->nome, encontrado->quantidade, encontrado->quilates, encontrado->material);
    printf("----------------------------------------------------------------\n");
        return encontrado;

        } else {

        if(chave > temp->dado->chave)
            temp = temp->dir;
        else
            temp = temp->esq;                
        }
      }
    }

  printf("----------------------------\n");
  printf("       ID Nao Encontrado    \n");
  printf("----------------------------\n");
    return NULL;
}

void imprimirBst(arvoreBST raiz, tabela * tab) {
  produto * temp = (produto *) malloc (sizeof(produto));
    printf("----------------------------------------------------------------\n");
  if (!temp) {
    printf("Erro: falha ao alocar memória.\n");
    return;
  }
  if (fseek(tab->arquivo, raiz->dado->indice, SEEK_SET) != 0) {
    printf("Erro: falha ao posicionar o ponteiro do arquivo.\n");
    return;
  }
    if (fread(temp, sizeof(produto), 1, tab->arquivo) != 1) {
    printf("Erro: falha ao ler dados do arquivo.\n");
    return;
  }

  int tam;
  fread(&tam, sizeof(int), 1, tab->arquivo);
  fread(temp->nome, sizeof(char), tam, tab->arquivo);

  printf("----------------------------------------------------------------\n");
  printf("ID: %d, Nome: %s, Quantidade: %d, Quilates: %d, Material: %s\n", raiz->dado->chave,temp->nome, temp->quantidade, temp->quilates, temp->material);
  free(temp);
    printf("--------------------------------------------------------------\n");
}

void inOrderBst(arvoreBST raiz, tabela* tab) {
  if(tab->arvoreBstIndice == NULL){

    printf("------------------------------------\n");
    printf("             Arvore Vazia           \n");
    printf("------------------------------------\n");

    return;
  }
  if(raiz != NULL) {
    inOrderBst(raiz->esq, tab);
    imprimirBst(raiz, tab);
    inOrderBst(raiz->dir, tab);
  }

}

// ------------ R B ------------ 

produto *procurarJoiassRB(tabela *tab, int chave) {
    if(tab->arquivo != NULL) {
    noRB *temp;
    temp = tab->arvoreRbIndice;
    while(temp!=NULL){
        if(temp->dado->chave == chave) {

    fseek(tab->arquivo, temp->dado->indice, SEEK_SET);

    produto * encontrado = (produto*) malloc(sizeof(produto));
    fread(encontrado, sizeof(produto), 1, tab->arquivo);

    int tam;
    fread(&tam, sizeof(int),1, tab->arquivo);
    fread(encontrado->nome, sizeof(char), tam, tab->arquivo);

    printf("-----------------------------------------------------------\n");
    printf("ID: %d, Nome: %s, Quantidade: %d, Quilates: %d, Material: %s\n", encontrado->id, encontrado->nome, encontrado->quantidade, encontrado->quilates, encontrado->material);
    printf("-----------------------------------------------------------\n");
        return encontrado;
        } else {
        if(chave > temp->dado->chave)
            temp = temp->direito;
        else
            temp = temp->esquerdo;                
        }
      }
    }
  printf("------------------------------\n");
  printf("   Quantidade Nao Encontrada  \n");
  printf("------------------------------\n");
    return NULL;
}

void buscarRb(int chave, arvoreRB raiz, tabela *tab){
    if(raiz != NULL) {
        buscarRb(chave,raiz->esquerdo, tab);
        if(chave == raiz->dado->chave){
            imprimirRb(raiz, tab);
        }
        buscarRb(chave,raiz->direito, tab);
    }
    else if(tab->arvoreRbIndice == NULL){
    printf("-----------------------------\n");
    printf("  Quantidade Nao Encontrada  \n");
    printf("-----------------------------\n");
      return;
    }
}

void imprimirRb(arvoreRB raiz, tabela * tab) {
  produto *temp = (produto*) malloc(sizeof(produto));
  printf("----------------------------------------------------------------\n");
  if (!temp) {
    printf("Erro: falha ao alocar memória.\n");
    return;
  }
  if (fseek(tab->arquivo, raiz->dado->indice, SEEK_SET) != 0) {
    printf("Erro: falha ao posicionar o ponteiro do arquivo.\n");
    return;
  }
    if (fread(temp, sizeof(produto), 1, tab->arquivo) != 1) {
    printf("Erro: falha ao ler dados do arquivo.\n");
    return;
  }

  int tam;
  fread(&tam, sizeof(int), 1, tab->arquivo);
  fread(temp->nome, sizeof(char), tam, tab->arquivo);

  printf("ID: %d, Nome: %s, Quantidade: %d, Quilates: %d, Material: %s\n",raiz->dado->chave, temp->nome, temp->quantidade, temp->quilates, temp->material);
  free(temp);
  printf("----------------------------------------------------------------\n");
}


void inOrderRb(arvoreRB raiz, tabela* tab) {
  if(tab->arvoreRbIndice == NULL){
    printf("------------------------------------\n");
    printf("             Arvore Vazia           \n");
    printf("------------------------------------\n");
    return;
  }

  else if(raiz != NULL) {
    inOrderRb(raiz->esquerdo, tab);
    imprimirRb(raiz, tab);
    inOrderRb(raiz->direito, tab);
  }
}

// ------------ A V L ------------ 

produto *procurarJoiasAvl(tabela *tab, int chave) {
    if(tab->arquivo != NULL){
    noAVL *temp;
    temp = tab->arvoreAvlIndice;
    while(temp!=NULL){
        if(temp->dado->chave == chave) {
        fseek(tab->arquivo, temp->dado->indice, SEEK_SET);

    produto * encontrado = (produto*) malloc(sizeof(produto));
    fread(encontrado, sizeof(produto), 1, tab->arquivo);

    int tam;
    fread(&tam, sizeof(int),1, tab->arquivo);
    fread(encontrado->nome, sizeof(char), tam, tab->arquivo);

      printf("-----------------------------------------------------------\n");
    printf("ID: %d, Nome: %s, Quantidade: %d, Quilates: %d, Material: %s\n", encontrado->id, encontrado->nome, encontrado->quantidade, encontrado->quilates, encontrado->material);
      printf("-----------------------------------------------------------\n");
    return encontrado;
        } else{
          if(chave && temp->dado->chave > 0)
              temp = temp->direito;
          else
              temp = temp->esquerdo;                
      }
      }
    }
  printf("--------------------------------\n");
  printf("       Lote Nao Encontrado      \n");
  printf("--------------------------------\n");
    return NULL;
}

void imprimirAvl(arvoreAVL raiz, tabela * tab) {
  produto *temp = (produto*) malloc(sizeof(produto));
    printf("----------------------------------------------------------------\n");
  if (!temp) {
    printf("Erro: falha ao alocar memória.\n");
    return;
  }
  if (fseek(tab->arquivo, raiz->dado->indice, SEEK_SET) != 0) {
    printf("Erro: falha ao posicionar o ponteiro do arquivo.\n");
    return;
  }
    if (fread(temp, sizeof(produto), 1, tab->arquivo) != 1) {
    printf("Erro: falha ao ler dados do arquivo.\n");
    return;
  }

  int tam;
  fread(&tam, sizeof(int), 1, tab->arquivo);
  fread(temp->nome, sizeof(char), tam, tab->arquivo);

  printf("ID: %d, Nome: %s, Quantidade: %d, Quilates: %d, Material: %s\n",raiz->dado->chave, temp->nome, temp->quantidade, temp->quilates, temp->material);
  free(temp);
  printf("----------------------------------------------------------------\n");
}

void inOrderAvl(arvoreAVL raiz, tabela* tab) {
  if(tab->arvoreAvlIndice == NULL){
    printf("------------------------------------\n");
    printf("             Arvore Vazia           \n");
    printf("------------------------------------\n");

    return;
  }
  else if(raiz != NULL) {
    inOrderAvl(raiz->esquerdo, tab);
    imprimirAvl(raiz, tab);
    inOrderAvl(raiz->direito, tab);
  }
}

// ------------ S A L V A R - B S T ------------ 

void salvarArquivoBst(char *nome, arvoreBST a) {
  FILE *arq;
  arq = fopen(nome, "wb");
  if(arq != NULL) {
    salvarAuxiliarBst(a, arq);
    fclose(arq);
  }
}

void salvarAuxiliarBst(arvoreBST raiz, FILE *arq){
  if(raiz != NULL) {		
    fwrite(raiz->dado, sizeof(indiceBST), 1, arq);
    salvarAuxiliarBst(raiz->esq, arq);
    salvarAuxiliarBst(raiz->dir, arq);
  }
}

arvoreBST carregarArquivoBst(char *nome, arvoreBST a) {
  FILE *arq;
  arq = fopen(nome, "rb");
  indiceBST * temp;
  if(arq != NULL) {
    temp = (indiceBST*) malloc(sizeof(indiceBST));
    while(fread(temp, sizeof(indiceBST), 1, arq)) {
      a = inserirBST(a, temp);			
      temp = (indiceBST*) malloc(sizeof(indiceBST));
    }
    fclose(arq);
  }
  return a;
}

// ------------ S A L V A R - A V L ------------

void salvarArquivoAvl(char *nome, arvoreAVL a) {
  FILE *arq;
  arq = fopen(nome, "wb");
  if(arq != NULL) {
    salvarAuxiliarAvl(a, arq);
    fclose(arq);
  }
}

void salvarAuxiliarAvl(arvoreAVL raiz, FILE *arq){
  if(raiz != NULL) {		
    fwrite(raiz->dado, sizeof(indiceAVL), 1, arq);
    salvarAuxiliarAvl(raiz->esquerdo, arq);
    salvarAuxiliarAvl(raiz->direito, arq);
  }
}

arvoreAVL carregarArquivoAvl(char *nome, arvoreAVL a) {
  FILE *arq;
  arq = fopen(nome, "rb");
  indiceAVL * temp;
  if(arq != NULL) {
    temp = (indiceAVL*) malloc(sizeof(indiceAVL));
    while(fread(temp, sizeof(indiceAVL), 1, arq)) {

      a = inserir_avl(temp, a);			
      temp = (indiceAVL*) malloc(sizeof(indiceAVL));

    }
    fclose(arq);
  }
  return a;
}

// ------------ S A L V A R - R B ------------ //

void salvarArquivoRb(char *nome, arvoreRB a) {
  FILE *arq;
  arq = fopen(nome, "wb");
  if(arq != NULL) {
    salvarAuxiliarRb(a, arq);
    fclose(arq);
  }
}

void salvarAuxiliarRb(arvoreRB raiz, FILE *arq){
  if(raiz != NULL) {		
    fwrite(raiz->dado, sizeof(indiceRB), 1, arq);
    salvarAuxiliarRb(raiz->esquerdo, arq);
    salvarAuxiliarRb(raiz->direito, arq);
  }
}

arvoreRB carregarArquivoRb(char *nome, arvoreRB a) {
  FILE *arq;
  arq = fopen(nome, "rb");
  indiceRB * temp;
  if(arq != NULL) {
    temp = (indiceRB*) malloc(sizeof(indiceRB));
    while(fread(temp, sizeof(indiceRB), 1, arq)) {

      inserirRB(temp, &a);			
      temp = (indiceRB*) malloc(sizeof(indiceRB));

    }
    fclose(arq);
  }
  return a;
}