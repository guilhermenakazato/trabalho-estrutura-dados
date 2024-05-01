#include <stdio.h>
#include "./include/libgeral.h"

void menu() {
    printf("Opções:\n1 - Inserir cidades na hash\n2 - Buscar cidade\n3 - Sair\n");
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
    int cidadesJaInseridas = 0;
    thash hash;

    do {
        menu();
        scanf("%d", &op);

        switch(op) {
            case 1:
                if(cidadesJaInseridas) {
                    printf("As cidades já foram inseridas na hash!\n\n");
                } else {
                    construir(&hash);
                    lerArquivo("data/municipios.json", &hash);
                    cidadesJaInseridas = 1;
                    printf("Cidades inseridas!\n\n");
                }

                break;
            case 2: 
                int codigo_ibge = 0;

                if(cidadesJaInseridas == 0) {
                    printf("Ainda não há nenhuma cidade na hash!\n\n");
                } else {
                    do {    
                        printf("Insira o código IBGE da cidade que deseja buscar: ");
                        scanf("%d", &codigo_ibge);

                        if(codigo_ibge <= 0) {
                            printf("Código inválido! Tente novamente.\n\n");
                        } else {
                            tcidade *cidade = buscar(hash, codigo_ibge);
                            infoCidade(*cidade);
                        }
                    } while(codigo_ibge <= 0);
                }

                break;
            case 3: 
                printf("Tchau!\n");
                deletarHash(&hash);
                break;
            default: 
                printf("Opção inválida!\n\n");
                break;
        }
    } while(op != 3);
}