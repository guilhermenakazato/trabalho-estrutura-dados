#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "./include/libgeral.h"

void menu()
{
    printf("Opções:\n1 - Buscar cidade\n2 - Buscar os N vizinhos mais próximos\n3 - Sair\n");
    printf("Insira a opção desejada: ");
}

void infoCidade(tcidade cidade) {
    printf("\nCódigo da cidade: %d\n", cidade.codigo_ibge);
    printf("Nome da cidade: %s\n", cidade.nome);
    printf("Latitude: %f\n", cidade.latitude);
    printf("Longitude: %f\n", cidade.longitude);
    printf("É capital? %s\n", cidade.capital == 0 ? "Não" : "Sim");
    printf("Código UF: %d\n", cidade.codigo_uf);
    printf("ID SIAFI: %d\n", cidade.siafi_id);
    printf("DDD: %d\n", cidade.ddd);
    printf("Fuso horário: %s\n\n", cidade.fuso_horario);
}

int main() {
    int op = 0;
    int cidadesJaInseridas;
    int n;
    int codigoIbge;
    thash hash;
    ttree arvore;
    theap heap;

    construirHash(&hash);
    construirArvore(&arvore);
    cidadesJaInseridas = lerArquivo("./data/municipios2.json", &hash, &arvore);

    if (cidadesJaInseridas == EXIT_SUCCESS) {
        do {
            menu();
            scanf("%d", &op);

            switch (op) {
            case 1:

                do {
                    printf("Insira o código IBGE da cidade que deseja buscar: ");
                    scanf("%d", &codigoIbge);

                    if (codigoIbge <= 0) {
                        printf("Código inválido! Tente novamente.\n\n");
                    } else {
                        tcidade *cidade = buscarHash(hash, codigoIbge);

                        if(cidade == NULL) {
                            printf("Cidade não encontrada.\n\n");
                        } else {
                            infoCidade(*cidade);
                        }
                    }
                } while (codigoIbge <= 0);
                break;
            case 2:                
                do {
                    printf("Insira o código IBGE da cidade: ");
                    scanf("%d", &codigoIbge);

                    if (codigoIbge <= 0) {
                        printf("Código inválido! Tente novamente.\n\n");
                    } else {
                        tcidade *cidade = buscarHash(hash, codigoIbge);
                        
                        if(cidade == NULL) {
                            printf("Cidade não encontrada.\n\n");
                            codigoIbge = -1;
                        } else {
                            printf("Insira a quantidade de vizinhos que deseja buscar: ");
                            scanf("%d", &n);

                            if(n <= 0) {
                                printf("Quantidade inválida! Tente novamente.\n\n");
                                codigoIbge = -1;
                            } else {
                                inicializaHeap(&heap, n);
                            }

                            tvizinho vizinhoMaisProximo = vizinhosProximos(&arvore.raiz, cidade, 0, &heap);
                            tcidade *cidade = buscarHash(hash, vizinhoMaisProximo.codigo_ibge);

                            infoCidade(*cidade);
                            printf("%d\n", heap.vizinhos[0].codigo_ibge);
                            printf("Distância: %.2f\n", vizinhoMaisProximo.distancia);
                        }
                    }
                } while (codigoIbge <= 0);

                break;
            case 3:
                printf("Tchau!\n");
                break;
            default:
                printf("Opção inválida!\n\n");
                break;
            }
        } while (op != 3);

        deletarHash(&hash);
        return EXIT_SUCCESS;
    } else {
        deletarHash(&hash);
        return EXIT_FAILURE;
    }
}