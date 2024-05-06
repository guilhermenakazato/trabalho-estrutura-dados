#include <stdio.h>
#include <stdlib.h>
#include "./include/libgeral.h"

void menu()
{
    printf("Opções:\n1 - Buscar cidade\n2 - Procurar vizinho mais próximo\n3 - Sair\n");
    printf("Insira a opção desejada: ");
}

void infoCidade(tcidade cidade) {
    printf("\nNome da cidade: %s\n", cidade.nome);
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
    thash hash;
    ttree arvore;

    construirHash(&hash);
    construirArvore(&arvore);
    cidadesJaInseridas = lerArquivo("./data/municipios.json", &hash, &arvore);

    if (cidadesJaInseridas == EXIT_SUCCESS) {
        do {
            menu();
            scanf("%d", &op);

            switch (op) {
            case 1:
                int codigoIbge;

                do {
                    printf("Insira o código IBGE da cidade que deseja buscar: ");
                    scanf("%d", &codigoIbge);

                    if (codigoIbge <= 0) {
                        printf("Código inválido! Tente novamente.\n\n");
                    } else {
                        tcidade *cidade = buscarHash(hash, codigoIbge);
                        infoCidade(*cidade);
                    }
                } while (codigoIbge <= 0);
                break;
            case 2:
                int codigoIbge;

                do {
                    printf("Insira o código IBGE da cidade que verifica buscar o vizinho mais próximo: ");
                    scanf("%d", &codigoIbge);

                    if (codigoIbge <= 0) {
                        printf("Código inválido! Tente novamente.\n\n");
                    } else {
                        vizinhosProximos()
                        tcidade *cidade = buscarHash(hash, codigoIbge);
                        infoCidade(*cidade);
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