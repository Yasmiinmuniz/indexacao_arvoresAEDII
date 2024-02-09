#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"
#include <string.h>

int inicializarTabela(tabela *tab) {
	tab->arquivo_dados = fopen("dados.dat", "r+b");
	tab->indiceBst  = NULL;
	tab->indice_avl = NULL;
	inicializar_rb(&tab->indice_rb);
	carregar_arquivo_arvore(tab, BST);
	carregar_arquivo_arvore(tab, AVL);
	carregar_arquivo_arvore(tab, RB);
	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}
void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}

int inserir_pokemon(tabela *tab, dado *pok) {
	int posicaoNovoRegistro, retorno;
	retorno = tab->arquivo_dados != NULL;
	if(retorno) {
		fseek(tab->arquivo_dados, 0L, SEEK_END);
		//diz onde está o cursor
		posicaoNovoRegistro = ftell(tab->arquivo_dados);
		
		//bst
		tab->indiceBst = adicionarBst(inicializarIndiceBst(posicaoNovoRegistro, pok->nome), tab->indiceBst);

		//avl
		tab->indice_avl = adicionar_avl(tab->indice_avl, inicializar_indice_avl(posicaoNovoRegistro, pok->codigo), NULL);
		
		// //rb
		inserir_rb(&tab->indice_rb, inicializar_indice_rb(posicaoNovoRegistro, pok->descricao));
		
		//salvar no arquivo de dados
		salvar_pokemon(tab->arquivo_dados, pok);
	}

	return retorno;
}

void salvar_pokemon(FILE *arq, dado *pok) {
	fprintf(arq, "%d;%s;", pok->removido, pok->nome);
	for(int i = 0; i<2; i++){
		fprintf(arq, "%d,", (int) pok->tipo[i]);
	}
	fprintf(arq, ";%f;%s;%d\n", pok->altura, pok->descricao, pok->codigo);
}

void remover_pokemon(tabela* tab, int indice) {
	if(tab != NULL){
		dado pok = buscar_pokemon(tab->arquivo_dados, indice);
		if(!pok.removido){
			tab->indiceBst = remover_bst(tab->indiceBst, pok.nome);
			tab->indice_avl = remover_elemento_avl(tab->indice_avl, pok.codigo, NULL);
			remover_rb(&tab->indice_rb,&tab->indice_rb, pok.descricao);
			fseek(tab->arquivo_dados, indice, SEEK_SET);
			char str[] = "1";
			fwrite(str, 1, sizeof(char), tab->arquivo_dados);
			fseek(tab->arquivo_dados, 0L, SEEK_END);
		}
		else
			printf("Erro ao remover\n");
	}
}



char* tipo_enum(int tipo) {
	switch(tipo) {
		case 0:
			return "Bug";
		case 1:
			return "Dark";
		case 2:
			return "Dragon";
		case 3:
			return "Eletric";
		case 4:
			return "Fairy";
		case 5:
			return "Fighting";
		case 6:
			return "Fire";
		case 7:
			return "Flying";
		case 8:
			return "Ghost";
		case 9:
			return "Grass";
		case 10:
			return "Ground";
		case 11:
			return "Ice";
		case 12:
			return "Normal";
		case 13:
			return "Poison";
		case 14:
			return "Psychic";
		case 15:
			return "Rock";
		case 16:
			return "Steal";
		case 17:
			return "Water";
	}
}

dado* ler_dados() {
	int tipo, op;
	dado* novo = (dado*) malloc(sizeof(dado));
	char * buffer = (char *) malloc(256 * sizeof(char));

	printf("Nome: ");
	scanf(" %[^\n]%*c", novo->nome);

	printf("Descricao: ");
	fgets(buffer, 256, stdin);
	novo->descricao = strdup(buffer);
	tirar_enter(novo->descricao);
	printf("Tipos disponiveis:\n");
	for(int i = 0; i<18; i++){
		printf("%d - %s\n", i+1, tipo_enum(i));
	}

	printf("Tipo: ");
	while (scanf("%d", &tipo) != 1 || tipo > 18) {
		printf("Insira um numero entre 1 e 18: ");
		while ((getchar()) != '\n');
	}
	novo->tipo[0] = (tipo_pokemon) tipo;
	printf("Deseja inserir um segundo tipo? (1 ou 0)\n");
	scanf("%d", &op);
	switch (op) {
		case 1:
			printf("Segundo tipo: ");
			while (scanf("%d", &tipo) != 1 || tipo > 18) {
			printf("Insira um numero entre 1 e 18: ");
			while ((getchar()) != '\n');
			}
			while ((getchar()) != '\n');
			break;
		case 0:
			tipo = 18;
			break;
	}
	novo->tipo[1] = (tipo_pokemon) tipo;

	printf("Altura: ");
	while (scanf("%f", &novo->altura) != 1) {
		printf("Insira apenas numeros: ");
		while ((getchar()) != '\n');
	}
	while (getchar() != '\n');

	printf("Codigo: ");
	while (scanf("%d", &novo->codigo) != 1) {
		printf("Insira apenas numeros: ");
		while ((getchar()) != '\n');
	}
	while (getchar() != '\n');
	free(buffer);
	novo->removido = 0;
	return novo;
}

void carregar_arquivo_arvore(tabela *tab, tipo_arvore tipo) {
	FILE *arq;
	size_t len;
	char nome[16], *linha = (char*) malloc(len), delim[] = ";";
	switch (tipo) {
	case BST:
		strcpy(nome, "indicesbst.dat");
		break;
	case AVL:
		strcpy(nome, "indicesavl.dat");
		break;
	case RB:
		strcpy(nome, "indicesrb.dat");
		break;
	}
	arq = fopen(nome, "r+");
  if(arq != NULL){
		while(getdelim(&linha, &len, '\n', arq) > 0){
  			char *ptr;
			ptr = strtok(linha, delim);
			int indice = atoi(ptr);
			ptr = strtok(NULL, delim);
			tirar_enter(ptr);
			switch (tipo) {
				case BST:
					tab->indiceBst = adicionarBst(inicializarIndiceBst(indice, ptr), tab->indiceBst);
					break;
				case AVL:
					tab->indice_avl = adicionar_avl(tab->indice_avl, inicializar_indice_avl(indice, atoi(ptr)), NULL);
					break;
				case RB:
					inserir_rb(&tab->indice_rb, inicializar_indice_rb(indice, ptr));
					break;
			}
		}
		fclose(arq);
 	}
 	free(linha);
}

dado buscar_pokemon(FILE *arq, int indice){
	dado temp;
	if(indice >= 0 ){ 
		if(arq != NULL){
			long len = sizeof(char) * 256;
			char *buffer = (char *) malloc(len);
			char delim[] = ";";
			dado temp;
			fseek(arq, indice, SEEK_SET);

			getline(&buffer, &len, arq);
			
			char *ptr = strtok(buffer, delim);
			temp.removido = atoi(ptr);

			ptr = strtok(NULL, delim);
			strcpy(temp.nome, ptr);
			
			ptr = strtok(NULL, ",");
			temp.tipo[0] = (tipo_pokemon) atoi(ptr);
			ptr = strtok(NULL, ",");
			temp.tipo[1] = (tipo_pokemon) atoi(ptr);
			ptr = strtok(NULL, delim);
			temp.altura = atof(ptr);

			ptr = strtok(NULL, delim);
			temp.descricao = (char*) malloc(sizeof(ptr));
			strcpy(temp.descricao, ptr);

			ptr = strtok(NULL, delim);
			temp.codigo = atoi(ptr);
			return temp;
		}
		printf("Arquivo invalido!\n");
	} else 
		printf("Indice invalido!\n");
	temp.removido = 1;
	return temp;
} 

void imprimir_elemento(dado pok){
	printf("Codigo: %d\n", pok.codigo);
	printf("Nome: %s\n", pok.nome);
	printf("Tipo(s):");
	printf("%s", tipo_enum((int)pok.tipo[0]));
	if(pok.tipo[1] != UNDEFINED)
		printf(", %s", tipo_enum((int)pok.tipo[1]));
	printf("\n");
	printf("Altura: %f\n", pok.altura);
	printf("Descricao: %s", pok.descricao);
	printf("\n");
}

void listar_por_nome(FILE *arq, bst raiz) {
	if(raiz != NULL) {
		listar_por_nome(arq, raiz->esq);
		printf("\n-----------------------------------------------\n\n");
		imprimir_elemento(buscar_pokemon(arq, raiz->dado->indice));
			// imprimir_elemento(pok);
		listar_por_nome(arq, raiz->dir);
	}
}

void listar_por_codigo(FILE *arq, avl raiz) {
	if(raiz != NULL) {
		listar_por_codigo(arq, raiz->esq);
		printf("\n-----------------------------------------------\n\n");
		imprimir_elemento(buscar_pokemon(arq, raiz->dado->indice));
		//if(!pok.removido)
			// imprimir_elemento(pok);
		listar_por_codigo(arq, raiz->dir);
	}
}

void listar_por_descricao(FILE *arq, rb raiz) {
	if(raiz != NULL) {
		listar_por_descricao(arq, raiz->esq);
		printf("\n-----------------------------------------------\n\n");
		//dado pok = 
		imprimir_elemento(buscar_pokemon(arq, raiz->dado->indice));
		//if(!pok.removido)
			
		listar_por_descricao(arq, raiz->dir);
	}
}

void salvar_arquivoBst(char *nome, bst a) {
	FILE *arq;
	arq = fopen(nome, "w+");
	if(arq != NULL) {
		salvar_auxiliarBst(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliarBst(bst raiz, FILE *arq){
	if(raiz != NULL) {
		fprintf(arq, "%d;%s\n", raiz->dado->indice, raiz->dado->nome);
		salvar_auxiliarBst(raiz->esq, arq);
		salvar_auxiliarBst(raiz->dir, arq);
	}
}

void salvar_arquivo_avl(char *nome, avl raiz) {
	FILE *arq;
	arq = fopen(nome, "w+");
	if(arq != NULL) {
		salvar_auxiliar_avl(raiz, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_avl(avl raiz, FILE *arq){
	if(raiz != NULL) {
		fprintf(arq, "%d;%d\n", raiz->dado->indice, raiz->dado->codigo);
		salvar_auxiliar_avl(raiz->esq, arq);
		salvar_auxiliar_avl(raiz->dir, arq);
	}

}

void salvar_arquivo_rb(char *nome, rb raiz) {
	FILE *arq;
	arq = fopen(nome, "w+");
	if(arq != NULL) {
		salvar_auxiliar_rb(raiz, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_rb(rb raiz, FILE *arq){
	if(raiz != NULL) {
		fprintf(arq, "%d;%s\n", raiz->dado->indice, raiz->dado->descricao);
		salvar_auxiliar_rb(raiz->esq, arq);
		salvar_auxiliar_rb(raiz->dir, arq);
	}

}

void finalizar (tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivoBst("indicesbst.dat", tab->indiceBst);
	salvar_arquivo_avl("indicesavl.dat", tab->indice_avl);
	salvar_arquivo_rb("indicesrb.dat", tab->indice_rb);
}