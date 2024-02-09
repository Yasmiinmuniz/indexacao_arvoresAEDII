#include <stdio.h>
#include "avl.h"
#include "avl.c"


int main() {
    NoAVL* raiz = NULL;

    // Inserir academias
    Academia academia1 = {"Academia A", 1, "12345", "987654321", "Mensal"};
    Academia academia2 = {"Academia B", 2, "54321", "123456789", "Anual"};
    Academia academia3 = {"Academia C", 3, "67890", "987654321", "Semestral"};

    raiz = inserirAVL(academia1, raiz);
    raiz = inserirAVL(academia2, raiz);
    raiz = inserirAVL(academia3, raiz);

    // Imprimir a árvore inordem
    printf("Árvore AVL (Inordem):\n");
    inordem(raiz);

    // Buscar uma academia por ID
    int idBusca = 2;
    NoAVL* resultadoBusca = buscar(idBusca, raiz);
    if (resultadoBusca != NULL) {
        printf("\n\nBuscar Academia com ID %d:\n", idBusca);
        printf("Nome: %s\nID: %d\nRG: %s\nTelefone: %s\nPlano: %s\n",
               resultadoBusca->academia.nome,
               resultadoBusca->academia.id,
               resultadoBusca->academia.rg,
               resultadoBusca->academia.telefone,
               resultadoBusca->academia.plano);
    } else {
        printf("\n\nNenhuma academia encontrada com ID %d.\n", idBusca);
    }

    // Remover uma academia por ID
    int idRemover = 1;
    raiz = remover(idRemover, raiz);

    // Imprimir a árvore inordem após a remoção
    printf("\n\nÁrvore AVL (Inordem) após remoção:\n");
    inordem(raiz);

    // Liberar a árvore AVL
    liberarAVL(raiz);

    return 0;
}
