#include <stdio.h>
#include <stdlib.h>
#include "avlL.h"

int altura_avl(avl a) {
	if(a == NULL) {
		return 0;
	} else {
		int esq = altura_avl(a->esq);
		int dir = altura_avl(a->dir);
	
		if(esq > dir)
			return esq + 1;
		else 
			return dir + 1;
		
	}
}

indice_avl* inicializar_indice_avl(int indice, int codigo)  {
	indice_avl *novo = (indice_avl*) malloc(sizeof(indice_avl));
	novo->indice = indice;
	novo->codigo = codigo;
	return novo;
}

int buscar_indice_avl(avl raiz, int codigo) {
	if(raiz != NULL) {
		if(raiz->dado->codigo == codigo) {
			return raiz->dado->indice;
		}
		else {
			if(raiz->dado->codigo > codigo)
				return buscar_indice_avl(raiz->esq, codigo);
			else 
				return buscar_indice_avl(raiz->dir, codigo);
		}
	} else {
		return -1;
	}
}


avl adicionar_avl(avl a, indice_avl *v, int *cresceu) {
    if(cresceu == NULL) {
        int c = 1;
        cresceu = &c;
    }
	//caso base a raiz eh vazia, ent cria um novo no
	if(a == NULL) {
		avl new = (avl) malloc(sizeof(no_avl));
		new->dado = v;
		new->esq = NULL;
		new->dir = NULL;
		new->fb = 0;
		*cresceu = 1;

		return new;
		
	} //caso não esteja, buscar onde inserir
	else {
		//se o valor for maior que a raiz, add elemento a direita
		if(v->codigo > a->dado->codigo) {
			a->dir = adicionar_avl(a->dir, v, cresceu);

			//calcular os reajustes do fator de balanco
			if(*cresceu) {
				switch(a->fb){
					//arvore totalmente balancada e agr tem um fator no lado direito
					case 0:
						a->fb = 1;
					   *cresceu = 1;
					    break;
					
					//arvore tava pendendo pra esquerda, agr ficou equilibrada
					case -1:
						a->fb = 0;
						*cresceu = 0;
						break;

					//caso o fb no lado direito 1 e agr se torne 2, logo precisa ser balanceada
					case 1:
						//a->fb = 2;
						*cresceu = 0; 
						a = rotacao_avl(a);//como pendeu pra direita, rota para esquerda
						break;

				}
			}
		} 
		else {
			//elemento menor que a raiz, add elemento esquerda
			a->esq = adicionar_avl(a->esq, v, cresceu);

			//calcular os reajustes do fator de balanco
			if(*cresceu) {
				switch(a->fb) {
					//arvore balanceada e agr pende 1 para direita
					case 0:
						a->fb = -1;
						*cresceu = 1;
						break;
					//arvore pende um para esquerda e agr equilibra
					case 1:
						a->fb = 0;
						*cresceu = 0;
						break;

					//pendia 1 para esquerda e agr desbalanceia
					case -1:
						//a->fb = -2;
						*cresceu = 0;
						a = rotacao_avl(a);
						break;

				}
			}
		}
	}
	return a;
}
avl remover_elemento_avl(avl a, int v, int *diminuiu) {
//caso base: raiz vazia
	if(a == NULL) {
        *diminuiu = 0;
        return a;
    }

    if(diminuiu == NULL) {
        int d = 0;
        diminuiu = &d;
    }

  //valor encontrado, hora de remover
  	if(a->dado->codigo == v) {
    		if(a->esq == NULL && a->dir == NULL) {
    			free(a);
    			*diminuiu = 1;
    			return NULL;
    		}
    		//dois filhos
    		if(a->esq != NULL && a->dir != NULL) {
    			avl aux = a->esq;
    			//procura o sucesso para substituir o valor a ser removido
    			while(aux->dir != NULL)
    				aux = aux->dir;

    			a->dado = aux->dado;

    			a->esq = remover_elemento_avl(a->esq, aux->dado->codigo, diminuiu);

                switch(a->fb){
                        case 0:
                            a->fb = 1;
                            *diminuiu = 0;
                            break;
                        case -1:
                            a->fb = 0;
                            *diminuiu = 1;
                            break;
                        case 1:
                            *diminuiu = 1;
                            a = rotacao_avl(a);
                    }
                    return a;

    		}
    		else { //caso a raiz so tenha um filho
    			avl aux;
    			*diminuiu = 1;
    			if(a->dir != NULL && a->esq == NULL){
    				aux = a->dir;
    			}
    			else {
    				aux = a->esq;
    				
    			}
    			free(a);
    			return aux;
    		} 
		}


		else {
			if(v > a->dado->codigo) {
		    		a->dir = remover_elemento_avl(a->dir, v, diminuiu);

		    		if(*diminuiu) 
		    		{
		    			switch(a->fb)
		    			{	
		    				//raiz pendendo esquerda, agr que removeu ela, gerou -2. Ou seja
		    					//rotacao_avl
		    				case -1:
		    					a->fb = -2;
		    					if(a->esq->fb == 0)
		    					{
		    						*diminuiu = 0;
		    					}
		    					else { 
		    						*diminuiu = 1; 
		    					}
		    					a = rotacao_avl(a);
		    					break;

		    				//raiz balanceadaaaaaaaa, agr pende pra esquerda
		    				case 0:
		    					a->fb = -1;
		    					*diminuiu = 0;
		    					break;

		    				//
		    				case 1:
		    					a->fb = 0;
		    					*diminuiu = 1;
		    					break;
		    			}
		    		}
		    	}
		    else {
		    		a->esq = remover_elemento_avl(a->esq, v, diminuiu);

		    		if(*diminuiu) 
		    		{
		    			switch(a->fb) 
		    			{
		    				//raiz estava pendendo pra esquerda, agr equilibrou
		    				case -1:
		    					a->fb = 0;
		    					*diminuiu = 1;
		    					break;

		    				//a raiz estava balanceada, apos remover ela passa a pendera direita
		    				case 0:
		    					a->fb = 1;
		    					*diminuiu = 0;
		    					break;

		    				//a raiz pendia para direita, apos remover outro na esquerda, ela passa
		    					//a a pender 2. Logo precisa ser rotacionada
		    				case 1:
		    					a->fb = 2;
		    					if(a->dir->fb == 0){
		    						*diminuiu = 0;
		    					}
		    					else { *diminuiu = 1; }

		    					a = rotacao_avl(a);//rotacao_avl esquerda
		    					break;
		    			}
		    		}
		    	}
		}
		    	//valor a ser removido maior que a raiz
    	
	return a;

}
//chamar todas rotacoes
//e verificar qual o desbalanceamento atraves dos ifs
//e ajustar para cada caso especifico
avl rotacao_avl(avl a){
    if (a->fb > 0){
        if(a->dir->fb >= 0){
            return rotacao_simples_esquerda_avl(a);
        }else{
            return rotacao_dupla_esquerda_avl(a);
        }
    }else{
        if (a->esq->fb <= 0){
            return rotacao_simples_direita_avl(a);
        }else{
            return rotacao_dupla_direita_avl(a);
        }

    }
}

/*
		(p)						(u)
	   /   \                   /   \
	 (t1)	(u)       ==>	 (p)	(t3)
	 	   /   \			/	\   
	 	(t2)   (t3)		  (t1)  (t2) 
  
*/

avl rotacao_simples_esquerda_avl(avl a) {
	//quem ta desbalanceado eh p
	// fb(p) == 2, fb(u) == 1
	avl p, u;
	p = a;
	u = p->dir;

	//corrigindo fatores de balanco
	u->fb = 0;
	p->fb = 0;

	//rotacao_avl
	p->dir = u->esq;
	u->esq = p;

	return u;
}
/*
		(p)					(u)
	   /   \               /   \
	 (u)	(t3)  ==>	 (t1)	(p)
	/   \			            /  \   
 (t1)   (t2)		          (t2) (t3)                           
*/


avl rotacao_simples_direita_avl(avl a) {
	//fb(p) == -2, fb(u) == -1
	avl p, u;

	p = a;
	u = p->esq;

	//corrigindo fatores de balanco
	u->fb = 0;
	p->fb = 0;
	
	//rotação
	p->esq = u->dir;
	u->dir = p;

	return u;
}

// avl rotacao_dupla_direita_avl(avl a) {
// 	avl p, u;
// 	p = a;
// 	u = p->esq;

// 	//corrigindo fatores de balanco
// 	u->fb = 1;
// 	p->fb = -1;

// 	p->esq = u->dir;
// 	u->dir = p;
	
// 	return u;
// }	


/*
 /*  (p)             (p)             (v)
     / \             / \             / \
    t1 (u)     =>   t1 (v)    =>   (p) (u)
       / \             / \         / \  / \
     (v)  t4          t2 (u)      t1 t2 t3 t4
     / \                 / \
    t2  t3              t3  t4
 */

avl rotacao_dupla_esquerda_avl(avl a){
 	//fb(p) = 2, fb(u) = -1
    avl p, u, v;

    p = a;
    u = p->dir;
    v = u->esq;

    //Rotação direita
    u->esq = v->dir;
    v->dir = u;
    p->dir = v;

    //Rotção esquerda
    p->dir = v->esq;
    v->esq = p;
    
    //Atualizando os fatores de balanço
    if(v->fb==0){  
        u->fb = 0;
        v->fb = 0;
        p->fb=0;
    
    }    
    else if(v->fb==-1){  

        u->fb = 1;
        v->fb = 0;
        p->fb = 0;
    }   
     else{  
        u->fb = 0;
        v->fb = 0;
        p->fb =-1;
    }
   return v;
}


 /*   p               p               v
     / \             / \             / \
    u  t4     =>    v   t4    =>    u    p
   / \             / \             / \  / \
  t1  v           u  t3           t1 t2 t3 t4
     / \         / \
    t2  t3      t1  t2
 */


avl rotacao_dupla_direita_avl(avl a) {
	//fb(p) = -2, fb(u) = 1
	avl p, u, v;

	p = a;
	u = p->esq;
   v = u->dir;

    // Rotação à esquerda    
    u->dir = v->esq;
    v->esq = u;
    p->esq = v;
    
    //Rotação á direita
    p->esq=v->dir;
    v->dir = p;
    
    //Atualizando os fatores de balanço
    if(v->fb == 0){ 

        u->fb = 0;
        p->fb = 0;
        v->fb = 0;
    }
    else if(v->fb==-1){

        u->fb = 0;
        v->fb = 0;
        p->fb = 1;

    }
    else {

        u->fb = -1;
        v->fb = 0;
        p->fb = 0;

    }
    return v;
}

void pre_order_avl(avl raiz) {
	if(raiz != NULL) {
		imprimir_elemento_avl(raiz);
		pre_order_avl(raiz->esq);
		pre_order_avl(raiz->dir);
	}
}

void pos_order_avl(avl raiz) {
	if(raiz != NULL) {
		pos_order_avl(raiz->esq);
		pos_order_avl(raiz->dir);
		imprimir_elemento_avl(raiz);
	}
}

void in_order_avl(avl raiz) {
	if(raiz != NULL) {
		in_order_avl(raiz->esq);
		imprimir_elemento_avl(raiz);
		in_order_avl(raiz->dir);
	}
}

void imprimir_elemento_avl(avl raiz) {
	if(raiz != NULL) {
		printf("%d | ", raiz->dado->codigo);

	}
}