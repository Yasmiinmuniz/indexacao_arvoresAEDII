#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

// Função para criar um novo nó de árvore Rubro-Negra
arvoreRB criarNoRB(indiceRB *valor){
   arvoreRB novo = (arvoreRB)malloc(sizeof(noRB));
   novo->dado = valor;
   novo->pai = NULL;
   novo->esquerdo = NULL;
   novo->direito = NULL;
   novo->cor = VERMELHO;
   return novo;
}

// Função para verificar a cor de um nó na árvore Rubro-Negra
int corRB(arvoreRB no) {
   if(no == NULL || no->cor == PRETO) {
    return 1; // Se for preto
   }
   else {
    return 0; // Se for vermelho
   }
}

// Função para verificar se um nó é filho esquerdo de seu pai
int ehEsquerdoRB(arvoreRB no) {
   if(no == no->pai->esquerdo) {
    return 1; // Se o nó for filho esquerdo do pai
   }
   else {
    return 0; // Se o nó não for filho esquerdo do pai
   }
}

int ehRaizRB(arvoreRB no) {
   if(no->pai == NULL) {
    return 1; // Se o nó for raiz
   }
   else {
    return 0; // Se o nó não for raiz
   }
}

arvoreRB tioRB(arvoreRB n) {
   if(ehEsquerdoRB(n->pai)) {
    return n->pai->pai->direito; // Se o nó for filho esquerdo do pai, retorna o tio
   }
   else {
    return n->pai->pai->esquerdo; // Se o nó for filho direito do pai, retorna o tio
   }
}

void rotacaoSimplesDireitaRB(arvoreRB *raiz, arvoreRB no, int simples){
   arvoreRB aux, temp;

   aux = no->esquerdo;
   temp = aux->direito;

   no->esquerdo = temp;
   aux->direito = no;

   if(simples){
    aux->cor = PRETO;
    no->cor = VERMELHO;
   }

   if(temp != NULL) {
    temp->pai = no;

    aux->pai = no->pai;
   }
  
   if(ehRaizRB(no)){
      *raiz = aux;
   } else {
      if(ehEsquerdoRB(no)){
        no->pai->esquerdo = aux;
      } else {
        no->pai->direito = aux;
      }
   }
   no->pai = aux;
}

void rotacaoSimplesEsquerdaRB(arvoreRB* raiz, arvoreRB no, int simples){
   arvoreRB aux, temp;

   aux = no->direito;
   temp = aux->esquerdo;

   no->direito = temp;
   aux->esquerdo = no;

   if(simples){
    aux->cor = PRETO;
    no->cor = VERMELHO;
   }

   if(temp != NULL){
    temp->pai = no;
   }

   aux->pai = no->pai;

   if(ehRaizRB(no)){
      *raiz = aux;
   } else {
      if(ehEsquerdoRB(no)){
         no->pai->esquerdo = aux;
      } else {
         no->pai->direito = aux;
      }
   }
   no->pai = aux;

}

void rotacaoDuplaEsquerdaRB(arvoreRB* raiz, arvoreRB no){
   rotacaoSimplesDireitaRB(raiz, no->direito, 0);
   rotacaoSimplesEsquerdaRB(raiz, no, 0);

   no->pai->cor = PRETO;
   no->cor = VERMELHO;
}

void rotacaoDuplaDireitaRB(arvoreRB* raiz, arvoreRB no){
   rotacaoSimplesEsquerdaRB(raiz, no->esquerdo, 0);
   rotacaoSimplesDireitaRB(raiz, no, 0);

   no->pai->cor = PRETO;
   no->cor = VERMELHO;
}

//Ajustar após a inserção de um nó
void ajustarRB(arvoreRB* raiz, arvoreRB no){
   if(ehRaizRB(no)){
      no->cor = PRETO;
      return;
   } else if(no->pai->cor == VERMELHO){
      if(corRB(tioRB(no)) == VERMELHO){ 
         no->pai->cor = PRETO;
         tioRB(no)->cor = PRETO;
         no->pai->pai->cor = VERMELHO;
         ajustarRB(raiz, no->pai->pai);
      } else { 
         if(ehEsquerdoRB(no) && ehEsquerdoRB(no->pai)){ 
            rotacaoSimplesDireitaRB(raiz, no->pai->pai, 1);

         } else if(!ehEsquerdoRB(no) && !ehEsquerdoRB(no->pai)){ 
            rotacaoSimplesEsquerdaRB(raiz, no->pai->pai, 1);

         } else if(ehEsquerdoRB(no) && !ehEsquerdoRB(no->pai)){ 
            rotacaoDuplaEsquerdaRB(raiz, no->pai->pai);

         } else if(!ehEsquerdoRB(no) && ehEsquerdoRB(no->pai)){ 
            rotacaoDuplaDireitaRB(raiz, no->pai->pai);
         }
      }
   }
}

void inserirRB(indiceRB *valor, arvoreRB* raiz){ 
   arvoreRB temp, pai, novo;
   temp  = *raiz;
   pai = NULL;

   while(temp != NULL){
      pai = temp;
      if(valor->chave > temp->dado->chave){
         temp = temp->direito;
      } else {
         temp = temp->esquerdo;
      }
   }

   novo = criarNoRB(valor);
   novo->pai = pai;

   if(ehRaizRB(novo)){
      *raiz = novo;
   } else if(valor->chave < pai->dado->chave){
      pai->esquerdo = novo;
   } else {
      pai->direito = novo;
   }
   ajustarRB(raiz, novo);
}

void ajustarRemocaoRB(arvoreRB* raiz, arvoreRB filho, arvoreRB pai) {
    arvoreRB irmao;
    
    while ((filho == NULL || filho->cor == PRETO) && filho != *raiz) {
        if (filho == pai->esquerdo) {
            irmao = pai->direito;
            
            if (irmao->cor == VERMELHO) {
                irmao->cor = PRETO;
                pai->cor = VERMELHO;
                rotacaoSimplesEsquerdaRB(raiz, pai, 1);
                irmao = pai->direito;
            }
            
            if ((irmao->esquerdo == NULL || irmao->esquerdo->cor == PRETO) &&
                (irmao->direito == NULL || irmao->direito->cor == PRETO)) {
                irmao->cor = VERMELHO;
                filho = pai;
                pai = filho->pai;
            } else {
                if (irmao->direito == NULL || irmao->direito->cor == PRETO) {
                    irmao->esquerdo->cor = PRETO;
                    irmao->cor = VERMELHO;
                    rotacaoSimplesDireitaRB(raiz, irmao, 1);
                    irmao = pai->direito;
                }
                
                irmao->cor = pai->cor;
                pai->cor = PRETO;
                irmao->direito->cor = PRETO;
                rotacaoSimplesEsquerdaRB(raiz, pai, 1);
                filho = *raiz;
                break;
            }
        } else {
            irmao = pai->esquerdo;
            
            if (irmao->cor == VERMELHO) {
                irmao->cor = PRETO;
                pai->cor = VERMELHO;
                rotacaoSimplesDireitaRB(raiz, pai, 1);
                irmao = pai->esquerdo;
            }
            
            if ((irmao->direito == NULL || irmao->direito->cor == PRETO) &&
                (irmao->esquerdo == NULL || irmao->esquerdo->cor == PRETO)) {
                irmao->cor = VERMELHO;
                filho = pai;
                pai = filho->pai;
            } else {
                if (irmao->esquerdo == NULL || irmao->esquerdo->cor == PRETO) {
                    irmao->direito->cor = PRETO;
                    irmao->cor = VERMELHO;
                    rotacaoSimplesEsquerdaRB(raiz, irmao, 1);
                    irmao = pai->esquerdo;
                }
                
                irmao->cor = pai->cor;
                pai->cor = PRETO;
                irmao->esquerdo->cor = PRETO;
                rotacaoSimplesDireitaRB(raiz, pai, 1);
                filho = *raiz;
                break;
            }
        }
    }
    
    if (filho != NULL) {
        filho->cor = PRETO;
    }
}

arvoreRB buscarRB(arvoreRB raiz, int chave) {
    if (raiz == NULL || raiz->dado->chave == chave) {
        return raiz;
    }
    else{
        if (chave < raiz->dado->chave) {
        return buscarRB(raiz->esquerdo, chave);
        }
        else {
        return buscarRB(raiz->direito, chave);
        }
    }

}

 void removerRB(arvoreRB* raiz, int chave){
    arvoreRB filho, pai, sucessor;
    arvoreRB removido;
    int corRemovido;

    removido = buscarRB(*raiz, chave);
    if(removido == NULL){
      return;
    }

    if(removido->esquerdo != NULL && removido->direito != NULL){
        sucessor = removido->direito;
        while(sucessor->esquerdo != NULL){
         sucessor = sucessor->esquerdo;
        }
        removido->dado = sucessor->dado;
        removido = sucessor;
    }

    corRemovido = removido->cor;
    if (removido->esquerdo == NULL) {
      filho = removido->direito;
    } else {
      filho = removido->esquerdo;
    }
    pai = removido->pai;
    if(filho != NULL){
      filho->pai = pai;
    }

    if(pai == NULL){
      *raiz = filho;
    }
    else{
        if(removido == pai->esquerdo){
         pai->esquerdo = filho;
        }
        else{
         pai->direito = filho;
        }
    }

    if(corRemovido == PRETO){
      ajustarRemocaoRB(raiz, filho, pai);
    }

    free(removido);
}