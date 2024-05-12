#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "./include/libgeral.h"

char *chaveIBGE(tcidade *cidade) {
    return cidade->codigo_ibge;
}

char *chaveNome(tcidade *cidade) {
    return cidade->nome;
}

void menu() {
    printf("Opções:\n1 - Buscar cidade por código IBGE\n2 - Buscar os N vizinhos mais próximos por código IBGE\n3 - Buscar os N vizinhos mais próximos usando o nome\n4 - Sair\n");
    printf("Insira a opção desejada: ");
}

void infoCidade(tcidade *cidade, theap *heap, thash hash, int n) {
    if (n == 1) {
        printf("\nCódigo da cidade: %s\n", cidade->codigo_ibge);
        printf("Nome da cidade: %s\n", cidade->nome);
        printf("Latitude: %f\n", cidade->latitude);
        printf("Longitude: %f\n", cidade->longitude);
        printf("É capital? %s\n", cidade->capital == 0 ? "Não" : "Sim");
        printf("Código UF: %d\n", cidade->codigo_uf);
        printf("ID SIAFI: %d\n", cidade->siafi_id);
        printf("DDD: %d\n", cidade->ddd);
        printf("Fuso horário: %s\n\n", cidade->fuso_horario);
    } else {
        printf("\nVizinhos mais próximos de %s:\n", cidade->nome);
        printf("%4s |%11s |%11s | %-31s |%11s |%11s |%8s | %s | %s | %s | %-28s |\n",
               "", "Distância", "Cód. IBGE", "Nome", "Latitude", "Longitude",
               "Capital", "UF", "Siafi ID", "DDD", "Fuso");
        for (int i = 0; i < heap->qtde_elementos; i++) {
            tcidade cidadeAtual = heap->vizinhos[i].cidade;

            printf("%4d |%8.2fkm |%10s | %-32s |%11f |%11f |   %s   | %d |%9d |%4d | %-28s |\n",
                   i + 1, heap->vizinhos[i].distancia * 100, cidadeAtual.codigo_ibge,
                   cidadeAtual.nome, cidadeAtual.latitude, cidadeAtual.longitude,
                   cidadeAtual.capital == 0 ? "Não" : "Sim", cidadeAtual.codigo_uf,
                   cidadeAtual.siafi_id, cidadeAtual.ddd, cidadeAtual.fuso_horario);
        }

        printf("\n");
    }
}

int main() {
    int op = 0;
    int cidadesJaInseridas;
    int n;
    char codigoIbge[10];
    thash hashIBGE;
    thash hashNome;
    ttree arvore;
    theap heap;
    tcidade *cidade;

    construirHash(&hashIBGE, chaveIBGE);
    construirHash(&hashNome, chaveNome);
    construirArvore(&arvore);
    cidadesJaInseridas = lerArquivo("./data/municipios.json", &hashIBGE, &hashNome, &arvore);

    if (cidadesJaInseridas == EXIT_SUCCESS) {
        do {
            menu();
            scanf("%d", &op);
            getchar();

            switch (op) {
            case 1:
                printf("Insira o código IBGE da cidade que deseja buscar: ");
                scanf("%s", codigoIbge);
                cidade = buscaPorIBGE(hashIBGE, codigoIbge);

                if (cidade == NULL) {
                    printf("Cidade não encontrada.\n\n");
                } else {
                    infoCidade(cidade, NULL, hashIBGE, 1);
                }
                break;
            case 2:
                printf("Insira o código IBGE da cidade: ");
                scanf("%s", codigoIbge);
                cidade = buscaPorIBGE(hashIBGE, codigoIbge);

                if (cidade == NULL) {
                    printf("Cidade não encontrada.\n\n");
                } else {
                    printf("Insira a quantidade de vizinhos que deseja buscar: ");
                    scanf("%d", &n);

                    if (n <= 0) {
                        printf("Quantidade inválida! Tente novamente.\n\n");
                    } else {
                        inicializaHeap(&heap, n);
                        vizinhosProximos(&arvore.raiz, cidade, 0, &heap);
                        heap_sort(heap.vizinhos, heap);
                        infoCidade(cidade, &heap, hashIBGE, 2);
                    }
                }
                break;
            case 3:
                char nome[50];
                printf("Insira o nome da cidade: ");
                scanf("%[^\n]s", nome);
                cidade = buscaPorNome(hashNome, nome);

                if (cidade == NULL) {
                    printf("Cidade não encontrada.\n\n");
                } else {
                    printf("Insira a quantidade de vizinhos que deseja buscar: ");
                    scanf("%d", &n);
                
                    if (n <= 0) {
                        printf("Quantidade inválida! Tente novamente.\n\n");
                    } else {
                        inicializaHeap(&heap, n);
                        vizinhosProximos(&arvore.raiz, cidade, 0, &heap);
                        heap_sort(heap.vizinhos, heap);
                        infoCidade(cidade, &heap, hashNome, 2);
                    }
                }
                break;
            case 4: 
                printf("Tchau!\n");
                break;
            default:
                printf("Opção inválida!\n\n");
                break;
            }
        } while (op != 3);

        destruirArvore(&arvore.raiz);
        deletarHash(&hashIBGE);
        deletarHash(&hashNome);
        return EXIT_SUCCESS;
    } else {
        destruirArvore(&arvore.raiz);
        deletarHash(&hashIBGE);
        deletarHash(&hashNome);
        return EXIT_FAILURE;
    }
}