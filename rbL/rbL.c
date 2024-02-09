#include "rbL.h"
#include <stdio.h>
#include <stdlib.h>

rb no_null;

indice_rb* inicializar_indice_rb(int indice, char *descricao)  {
	indice_rb *novo = (indice_rb*) malloc(sizeof(indice_rb));
	novo->indice = indice;
	novo->descricao = (char*) malloc(sizeof(char));
	strcpy(novo->descricao, descricao);
	return novo;
}

void inicializar_rb(rb *raiz) {
	*raiz = NULL;
	no_null = (rb) malloc(sizeof(struct no_rb));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
	no_null->esq = NULL;
	no_null->dir = NULL;
}

int eh_raiz_rb(rb elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo_rb(rb elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}
int eh_filho_direito_rb(rb elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

rb eh_irmao_rb(rb elemento) {
	//se ele eh o filho esquerdo, retorna o filho do nodo acima dele, a direita
	if(eh_filho_esquerdo_rb(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}

rb tio_rb(rb elemento) {
	return eh_irmao_rb(elemento->pai);
}


enum cor cor_rb(rb elemento) {
	enum cor c;
	if(elemento == NULL)
		c = PRETO;
	else
		c = elemento->cor;
	return c;
}
	
int altura_rb(rb a) {
	if(a == NULL) 
		return 0;
	else {
		int esq, dir;
		esq = altura_rb(a->esq);
		dir = altura_rb(a->dir);

		if(esq > dir)
			return (esq + 1);
		else
			return (dir + 1);
	}
}

indice_rb* maior_elemento_rb(rb raiz) {
	if(raiz == NULL)
		return NULL;
	if(raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento_rb(raiz->dir);
}

void imprimir_rb(rb raiz) {
	if(raiz != NULL) {
		imprimir_rb(raiz->esq);
		imprimir_elemento_rb(raiz);
		imprimir_rb(raiz->dir);
	}
}

void imprimir_elemento_rb(rb raiz) {
	switch(raiz->cor) {
		case PRETO:
			printf("\x1b[30m[%s]\x1b[0m", raiz->dado->descricao);
			break;
		case VERMELHO:
			printf("\x1b[31m[%s]\x1b[0m", raiz->dado->descricao);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%s]\x1b[0m", raiz->dado->descricao);
			break;
	}
}


void inserir_rb(rb *raiz, indice_rb *valor) {
	rb aux, pai, novo;
	aux = *raiz; 
	pai = NULL;

	while(aux != NULL) {
		pai = aux;
		//verificando para que lado devemos percorrer
		if(strcmp(aux->dado->descricao, valor->descricao) >= 0)
			aux = aux->esq;
		else
			aux = aux->dir;
	}

	novo = (rb) malloc(sizeof(struct no_rb));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if(eh_raiz_rb(novo)) {
		*raiz = novo;
	} else {
		if(strcmp(valor->descricao, pai->dado->descricao) > 0)
			pai->dir = novo;
		else  
			pai->esq = novo; 
	}

	//essa eh a raiz de toda a arvore, não a raiz relativa;
	//apos inserido o elemento, precisamos verificar a cor dele e afins
	ajustar_rb(raiz, novo);

}

void remover_rb(rb *raiz, rb* raiz_relativa, char* descricao) {
	rb aux = *raiz_relativa;

	while(aux != NULL) {
		if(strcmp(descricao, aux->dado->descricao) == 0) {
			//sem filhos
			if(aux->esq == NULL && aux->dir == NULL) {
				//remover_rb raiz sem filhos
				if(eh_raiz_rb(aux)) {
					*raiz = NULL;
					break;
				}
				//sem filhos, mas nao raiz
				if(aux->cor == VERMELHO) {
					if(eh_filho_esquerdo_rb(aux))
						aux->pai->esq = NULL;
					else
						aux->pai->dir = NULL;
					break;

				} else {
					/*se o elemento for preto, 
					precisa substituir pelo nonull */
					no_null->pai = aux->pai;

					if(eh_filho_esquerdo_rb(aux))
						aux->pai->esq = no_null;
					else 
						aux->pai->dir = no_null;

					reajustar_rb(raiz, no_null);
					break;
				}
			}
			//um filho

			//apenas o filho esquerdo
			if(aux->dir == NULL) {
				aux->esq->cor = PRETO;
				if(eh_raiz_rb(aux)) {
					*raiz = aux->esq;
				} else {
					if(eh_filho_esquerdo_rb(aux))
						aux->pai->esq = aux->esq;
					else 
						aux->pai->dir = aux->esq;
				}
				break;
			}
			//apenas filho direito
			if(aux->esq == NULL) {
				aux->dir->cor = PRETO;
				if(eh_raiz_rb(aux)) {
					*raiz = aux->dir;
				} else {
					if(eh_filho_esquerdo_rb(aux))
						aux->pai->esq = aux->dir;
					else
						aux->pai->dir = aux->dir;
				}
				break;
			}
			//dois filhos
			if(aux->dir != NULL && aux->esq != NULL) {
				aux->dado = maior_elemento_rb(aux->esq);
				remover_rb(raiz, &(aux->esq), aux->dado->descricao);
				break;
			}

		} else {
			if(strcmp(descricao, aux->dado->descricao) > 0)
				aux = aux->dir;
			else
				aux = aux->esq;
		}
	}
}

void reajustar_rb(rb *raiz, rb elemento) {
	
	//caso 1: eh a raiz
	if(eh_raiz_rb(elemento)) {
		elemento->cor = PRETO;

		return;
	}

	//caso 2: pai preto, irmao vermelho e sobrinhos preto
	if(cor_rb(elemento->pai) == PRETO &&
	 cor_rb(eh_irmao_rb(elemento)) == VERMELHO &&
	 (cor_rb(eh_irmao_rb(elemento)->dir) == PRETO || eh_irmao_rb(elemento)->dir == NULL) &&
	 (cor_rb(eh_irmao_rb(elemento)->esq) == PRETO || eh_irmao_rb(elemento)->esq == NULL)) {
		if(eh_filho_esquerdo_rb(elemento))
			rotacao_simples_esquerda_rb(raiz, elemento);
		else 
			rotacao_simples_direita_rb(raiz, elemento);

		elemento->pai->pai->cor = PRETO;
		elemento->pai->cor = VERMELHO;

		return;
	 }

	 //caso 3: pai, irmaos e sobrinhos pretos
	 if(cor_rb(elemento -> pai) == PRETO && cor_rb(eh_irmao_rb(elemento)) == PRETO &&
		(cor_rb(eh_irmao_rb(elemento)-> dir)  == PRETO || eh_irmao_rb(elemento) -> dir == NULL) && 
		(cor_rb(eh_irmao_rb(elemento) -> esq)  == PRETO || eh_irmao_rb(elemento) -> esq == NULL)){	
		eh_irmao_rb(elemento) -> cor = VERMELHO;
		retira_duplo_preto_rb(raiz, elemento);
		reajustar_rb(raiz, elemento->pai);

		return;
	}

	//caso 4: pai vermelho, irmao e sobrinhps preto
	if(cor_rb(elemento -> pai) == VERMELHO && 
		(cor_rb(eh_irmao_rb(elemento)) == PRETO || eh_irmao_rb(elemento) == NULL) &&
		(cor_rb(eh_irmao_rb(elemento)-> dir)  == PRETO || eh_irmao_rb(elemento) -> dir == NULL) && (cor_rb(eh_irmao_rb(elemento) -> esq) == PRETO || eh_irmao_rb(elemento) -> esq == NULL)){

			elemento -> pai -> cor = PRETO;
			eh_irmao_rb(elemento) -> cor = VERMELHO;
			
			retira_duplo_preto_rb(raiz, elemento); 

			return;

	}
	// CASO 5: irmão preto e um dos sobrinhos vermelho

	//caso 5a
	if(eh_filho_esquerdo_rb(elemento) && cor_rb(eh_irmao_rb(elemento)) == PRETO &&
		(cor_rb(eh_irmao_rb(elemento) -> dir) == PRETO || eh_irmao_rb(elemento) -> dir == NULL) && cor_rb(eh_irmao_rb(elemento) -> esq) == VERMELHO){
			
			rotacao_simples_direita_rb(raiz, eh_irmao_rb(elemento));
			eh_irmao_rb(elemento) -> cor = PRETO;
			eh_irmao_rb(elemento) -> dir -> cor = VERMELHO;
			
			reajustar_rb(raiz, elemento);

			return;
		}

	//caso 5b
	if(eh_filho_direito_rb(elemento) && cor_rb(eh_irmao_rb(elemento)) == PRETO &&
		(cor_rb(eh_irmao_rb(elemento) -> esq) == PRETO || eh_irmao_rb(elemento) -> esq == NULL) 		
		&& cor_rb(eh_irmao_rb(elemento) -> dir) == VERMELHO) {
		
			rotacao_simples_esquerda_rb(raiz, eh_irmao_rb(elemento));
			eh_irmao_rb(elemento) -> cor = PRETO;
			eh_irmao_rb(elemento) -> esq -> cor = VERMELHO;
			
			reajustar_rb(raiz, elemento);

			return;
	}

	//caso 6: irmao preto e um dos sobrinhos vermelho

	//caso 6a:
	if(eh_filho_esquerdo_rb(elemento) && 
		cor_rb(eh_irmao_rb(elemento)) == PRETO && 
		cor_rb(eh_irmao_rb(elemento) -> dir) == VERMELHO) {
		
		enum cor cor_original_pai = cor_rb(elemento -> pai);
		
		rotacao_simples_esquerda_rb(raiz, elemento -> pai);
		
		elemento -> pai -> pai -> cor = cor_original_pai;
		elemento -> pai -> cor = PRETO;
		tio_rb(elemento) -> cor = PRETO;		
		
		retira_duplo_preto_rb(raiz, elemento);

		return;
	}

	//caso 6b
	if(eh_filho_direito_rb(elemento) && 
		cor_rb(eh_irmao_rb(elemento)) == PRETO && 
		cor_rb(eh_irmao_rb(elemento) -> esq) == VERMELHO) {

		enum cor cor_original_pai = cor_rb(elemento -> pai);
		
		rotacao_simples_direita_rb(raiz, elemento -> pai);
		
		elemento -> pai -> pai -> cor = cor_original_pai;
		elemento -> pai -> cor = PRETO;
		tio_rb(elemento) -> cor = PRETO;		
		
		retira_duplo_preto_rb(raiz, elemento);

		return;
	}
}

void retira_duplo_preto_rb(rb *raiz, rb elemento) {
	if(elemento == no_null) {
		if(eh_filho_esquerdo_rb(elemento))
			elemento->pai->esq = NULL;
		else
			elemento->pai->dir = NULL;
	} else {
		elemento->cor = PRETO;
	}
}


void ajustar_rb(rb* raiz, rb novo) {
	
	//se o pai e o elemento forem vermelhos, precisa ajustar_rb
	while(cor_rb(novo->pai) == VERMELHO && cor_rb(novo) == VERMELHO) {
		//caso 1
		if(cor_rb(tio_rb(novo)) == VERMELHO){
			//tornando o tio_rb e pai do elemento inseido preto
			tio_rb(novo)->cor = PRETO;
			novo->pai->cor = PRETO;
			novo->pai->pai->cor = VERMELHO;

			//agr eu quero que verifique se o avo do elemento inserido
			//que se tornou vermelho, está na cor correta, ent eu atualizo
			novo = novo->pai->pai;

			continue;
		}
		//case 2a: rotacao simples direita
		if(eh_filho_esquerdo_rb(novo) && eh_filho_esquerdo_rb(novo->pai)) {
			//rotacao simples passando a raiz e o avo do elemento
			rotacao_simples_direita_rb(raiz, novo->pai->pai);
			novo->pai->cor = PRETO;
			novo->pai->dir->cor = VERMELHO;

			continue;
		}
		//caso 2b: rotacao simples esquerda
		if(eh_filho_direito_rb(novo) && eh_filho_direito_rb(novo->pai)) {
			rotacao_simples_esquerda_rb(raiz, novo->pai->pai);
			novo->pai->cor = PRETO;
			novo->pai->esq->cor = VERMELHO;

			continue;
		}
		//caso 3a: rotacao dupla direita
		if(eh_filho_direito_rb(novo) && eh_filho_esquerdo_rb(novo->pai)) {
			rotacao_simples_esquerda_rb(raiz, novo->pai);
			rotacao_simples_direita_rb(raiz, novo->pai);
			novo->dir->cor = VERMELHO;
			novo->esq->cor = VERMELHO;
			novo->cor = PRETO;

			continue;
		}
		//caso 3b: rotacao dupla esquerda
		if(eh_filho_esquerdo_rb(novo) && eh_filho_direito_rb(novo->pai)) {
            rotacao_simples_direita_rb(raiz, novo->pai);
            rotacao_simples_esquerda_rb(raiz, novo->pai);
            novo->dir->cor = VERMELHO;
            novo->esq->cor = VERMELHO;
            novo->cor = PRETO;
            
            continue;

		}
	}
	//Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta
	(*raiz)->cor = PRETO;
}

/*
		(p)					(u)
	   /   \               /   \
	 (u)	(t3)  ==>	 (t1)	(p)
	/   \			            /  \   
 (t1)   (t2)		          (t2) (t3)                           
*/


void rotacao_simples_direita_rb(rb *raiz, rb pivo) {
	rb p, u, t2;
	p = pivo;
	u = pivo->esq;
	t2 = u->dir;

	//para fazer a ligacao da raiz a sub-arvore com seu pai,
	//eh preciso saber se o pivo era um filho esquerdo ou direito

	int posicao_pivo_esq = eh_filho_esquerdo_rb(pivo);
	//pois ele precisa ser inserido em um dos lados do pai

	//trocando o lado do t2
	p->esq = t2;

	//se ele n for null, precisa linká-lo novamente
	if(t2 != NULL) 
		t2->pai = pivo;

	//agora fazendo a rotação dos elementos restantes
	u->dir = pivo;
	u->pai = p->pai;
	p->pai = u;

	p->cor = VERMELHO;
	u->cor = PRETO;

	//testando se u eh raiz, pois se for, a raiz da arvore recebe ele
	if(eh_raiz_rb(u))
		*raiz = u;

	//caso n seja, vamos descobrir se o pivo (valor que agr o u ocupa o lugar)
	//era filho esquerdo ou n para posicioná-lo corretamente
	//em relação ao pai
	else {
		if(posicao_pivo_esq)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}

/*
		(p)						(u)
	   /   \                   /   \
	 (t1)	(u)       ==>	 (p)	(t3)
	 	   /   \			/	\   
	 	(t2)   (t3)		  (t1)  (t2) 
  
*/
void rotacao_simples_esquerda_rb(rb *raiz, rb pivo) {
	rb p, u, t2;
	p = pivo;
	u = p->dir;
	t2 = u->esq;

	int posicao_pivo_dir = eh_filho_direito_rb(pivo);

	p->dir = t2;

	if(t2 != NULL)
		t2->pai = p;

	u->esq = p;
	u->pai = p->pai;
	p->pai = u;

	p->cor = VERMELHO;
	u->cor = PRETO;
	
	if(eh_raiz_rb(u))
		*raiz = u;
	else {
		if(posicao_pivo_dir)
			u->pai->dir = u;
		else
			u->pai->esq = u;
	}
}

void preorder_rb (rb raiz) {
  if (raiz != NULL) {
      imprimir_elemento_rb(raiz);
      preorder_rb (raiz->esq);
      preorder_rb (raiz->dir);
    }
}

int buscar_indice_rb(rb raiz, char* descricao) {
	if(descricao != NULL && raiz != NULL) {
		int cmp = strcmp(descricao, raiz->dado->descricao);
		if(cmp == 0) {
			return raiz->dado->indice;
		}
		else {
			if(cmp > 0)
				return buscar_indice_rb(raiz->dir, descricao);
			else 
				return buscar_indice_rb(raiz->esq, descricao);
		}
	} else {
		return -1;
	}
}