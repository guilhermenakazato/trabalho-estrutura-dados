#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libgeral.h"

int lerArquivo(const char *caminhoArquivo, thash *hashIBGE, thash *hashNome, ttree *arvore) {
    FILE* arquivo;
    arquivo = fopen(caminhoArquivo, "r");
    char linha[50];
    char atributos[][30] = {"codigo_ibge", "nome", "latitude",
                             "longitude", "capital", "codigo_uf",
                             "siafi_id", "ddd", "fuso_horario"};
    if(arquivo == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return EXIT_FAILURE;
    } else {
        tcidade cidade;
        char fuso_horario2[30];

        while(fgets(linha, 50, arquivo) != NULL) {
            if(strstr(linha, atributos[0]) != NULL) {
                sscanf(linha, "%*s %[^,]", cidade.codigo_ibge);
            } else if(strstr(linha, atributos[1]) != NULL) {
                sscanf(linha, "%*s \"%[^\"]", cidade.nome);
            } else if(strstr(linha, atributos[2]) != NULL) {
                sscanf(linha, "%*s %lf", &cidade.latitude);
            } else if(strstr(linha, atributos[3]) != NULL) {
                sscanf(linha, "%*s %lf", &cidade.longitude);
            } else if(strstr(linha, atributos[4]) != NULL) {
                sscanf(linha, "%*s %d", &cidade.capital);
            } else if(strstr(linha, atributos[5]) != NULL) {
                sscanf(linha, "%*s %d", &cidade.codigo_uf);
            } else if(strstr(linha, atributos[6]) != NULL) {
                sscanf(linha, "%*s %d", &cidade.siafi_id);
            } else if(strstr(linha, atributos[7]) != NULL) {
                sscanf(linha, "%*s %d", &cidade.ddd);
            } else if(strstr(linha, atributos[8]) != NULL) {
                sscanf(linha, "%*s \"America\\%[^\"]", fuso_horario2);
                strcpy(cidade.fuso_horario, "America");
                strcat(cidade.fuso_horario, fuso_horario2);

                inserirHash(hashIBGE, &cidade);
                inserirHash(hashNome, &cidade);
                inserirArvore(arvore, &arvore->raiz, cidade, 0);
            }
        }
    }

    fclose(arquivo);
    return EXIT_SUCCESS;
}