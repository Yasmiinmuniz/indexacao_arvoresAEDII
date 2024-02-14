#include <stdio.h>
#include <stdlib.h>
#include "joalheria.h"

int main(int argc, char * argv[]) {
    produto *p;
    tabela tab;
    int opcao, valor;
    inicializarTabela(&tab);

    while(1) {
        printf("------------------------------------\n");
        printf("               JOALHERIA            \n");
        printf("------------------------------------\n");
        printf("1 - ADICIONAR                       \n");
        printf("2 - PROCURAR                        \n");
        printf("3 - REMOVER                         \n");
        printf("4 - EM ORDEM                        \n");
        printf("99 - SAIR                           \n");
        printf("------------------------------------\n");
        scanf("%d", &opcao);
        printf("\n");
      
        switch(opcao) {
            case 1:
                adicionarProduto(&tab, ler_dados());
                break;
            case 2:
                printf("------------------------------------\n");
                printf("1 - BUSCAR POR ID                   \n");
                printf("2 - BUSCAR POR QUILATES             \n");
                printf("3 - BUSCAR POR QUANTIDADE           \n");
                printf("------------------------------------\n");
                scanf("%d", &opcao);
                printf("\n");
              
                switch(opcao){
                    case 1:
                        printf("------------------------------------\n");
                        printf("               JOALHERIA            \n");
                        printf("------------------------------------\n");
                        printf("\nInforme o ID que deseja buscar: ");
                        scanf("%d", &valor);
                        printf("\n");
                        p = procurarJoiasBST(&tab, valor);
                        break;
                    case 2:
                        printf("------------------------------------\n");
                        printf("               JOALHERIA            \n");
                        printf("------------------------------------\n");
                        printf("\nInforme os quilates da joia que deseja buscar: ");
                        scanf("%d", &valor);
                        printf("\n");
                        p = procurarJoiasAvl(&tab, valor);

                        break;
                    case 3:
                        printf("------------------------------------\n");
                        printf("               JOALHERIA            \n");
                        printf("------------------------------------\n");
                        printf("\nInforme a quantidade em estoque que deseja buscar: ");
                        scanf("%d", &valor);
                        printf("\n");
                        buscarRb(valor, tab.arvoreRbIndice, &tab);
                        break;
                }
                break;
            case 3:
                printf("------------------------------------\n");
                printf("               JOALHERIA            \n");
                printf("------------------------------------\n");
                printf("\nInforme o ID que deseja remover: ");
                scanf("%d", &valor);
                printf("\n");
                removerProduto(&tab, valor);
                break;
            case 4:
                printf("--------------------------\n");
                printf("         JOALHERIA        \n");
                printf("--------------------------\n");
                printf("\nInorder da Arvore BST - (ID):\n");
                inOrderBst(tab.arvoreBstIndice, &tab);
                printf("\n");
                printf("\nInorder da Arvore AVL - (Quilates):\n");
                inOrderAvl(tab.arvoreAvlIndice, &tab);
                printf("\n");
                printf("\nInorder da Arvore RB - (Quantidade):\n");
                inOrderRb(tab.arvoreRbIndice, &tab);
                printf("\n");
                break;
            case 99:
                finalizar(&tab);
                exit(0);
        }
    }
}
