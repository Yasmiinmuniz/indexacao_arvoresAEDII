#include "bst.h"
#include "bst.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
    No* raiz = NULL;

    // Teste de Inserir academias
    Academia usuario1 = {"Fulana", 1, "12345678", "9999-1234", "Mensal"};
    raiz = inserir(usuario1, raiz);

    Academia usuario2 = {"Ciclano", 2, "87654321", "8888-5678", "Semestral"};
    raiz = inserir(usuario2, raiz);

    Academia usuario3 = {"Beltana", 3, "24682468", "7777-9012", "Anual"};
    raiz = inserir(usuario3, raiz);

    // Imprimir usuarios em ordem
    printf("Imprimir registros:\n");
    inordem(raiz);

    // Buscar usuarios por ID
    int idBusca = 2;
    Academia resultadoBusca = busca(idBusca, raiz);
    printf("\nBuscar Usuarios (ID: %d):\n", idBusca);
    printf("Nome: %s, ID: %d, RG: %s, Telefone: %s, Plano: %s\n",
           resultadoBusca.nome, resultadoBusca.id, resultadoBusca.rg,
           resultadoBusca.telefone, resultadoBusca.plano);

    // Remover usuarios por ID
    int idRemover = 2;
    raiz = remover(idRemover, raiz);

    // Imprimir usuarios após remoção
    printf("\nImprimir usuarios apos remocao:\n");
    inordem(raiz);

    // Liberar a árvore
    liberarArvore(raiz);

    return 0;
}
