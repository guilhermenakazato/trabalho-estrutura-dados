#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../include/libgeral.h"
#define SEED 0x12345678
#define SIZE 10007

uint32_t hash1(const char *chave, uint32_t seed) {
    for (; *chave; ++chave)  {
        seed ^= *chave;
        seed *= 0x5bd1e995;
        seed ^= seed >> 15;
    }
    return abs(seed);
}

int hash2(const char *chave) {
    int valor = 1;

    while (*chave) {
        valor *= *chave++;
    }

    return 1 + valor;
}

int construirHash(thash *hash, char *(*pegar_chave)(tcidade *)) {
    hash->vetor = (tcidade *) calloc(SIZE, sizeof(tcidade));
    if(hash->vetor == NULL) {
        return EXIT_FAILURE;
    }

    hash->qtde_elementos = 0;
    hash->tamanho_max = SIZE;
    hash->pegarChave = pegar_chave;

    return EXIT_SUCCESS;
}

int inserirHash(thash *hash, tcidade *bucket) {
    int pos;
    int i = 0;

    do {
        uint32_t resultadoHash1 = hash1(hash->pegarChave(bucket), SEED);
        int resultadoHash2 = hash2(hash->pegarChave(bucket));
        pos = (resultadoHash1 + i * resultadoHash2) % hash->tamanho_max;

        i++;
    } while(hash->pegarChave(&hash->vetor[pos])[0] != 0);
    
    hash->vetor[pos] = *bucket;
    hash->qtde_elementos += 1;

    if(strcmp(hash->pegarChave(bucket), "5002704") == 0) {
        printf("%s\n", hash->vetor[pos].nome);
        printf("%s\n", hash->vetor[pos].codigo_ibge);
    }

    return EXIT_SUCCESS;
}

tcidade *buscaPorIBGE(thash hash, const char *chave) {
    int pos;
    int i = 0;

    do {
        uint32_t resultadoHash1 = hash1(chave, SEED);
        int resultadoHash2 = hash2(chave);
        pos = (resultadoHash1 + i * resultadoHash2) % hash.tamanho_max;

        if(strcmp(chave, hash.pegarChave(&hash.vetor[pos])) == 0)
            return &hash.vetor[pos];

        i++;
    } while(hash.pegarChave(&hash.vetor[pos])[0] != 0);

    return NULL;
}

char *buscaPorNome(thash hash, const char *chave) {
    int pos;
    int i = 0;
    int cidadesRepetidas = 0;
    
    tcidade *cidades;
    cidades = (tcidade *) malloc(sizeof(tcidade) * 10);

    do {
        uint32_t resultadoHash1 = hash1(chave, SEED);
        int resultadoHash2 = hash2(chave);
        pos = (resultadoHash1 + i * resultadoHash2) % hash.tamanho_max;

        if(strcmp(chave, hash.vetor[pos].nome) == 0) {
            cidades[cidadesRepetidas] = hash.vetor[pos];
            cidadesRepetidas++;
        }

        i++;
    } while(hash.pegarChave(&hash.vetor[pos])[0] != 0);

    if(cidadesRepetidas > 1) {
        int escolha;
        printf("Escolha uma das cidades abaixo:\n");
        printf("%4s |%11s | %-31s |%11s |%11s |%8s | %s | %s | %s | %-28s |\n",
               "", "Cód. IBGE", "Nome", "Latitude", "Longitude",
               "Capital", "UF", "Siafi ID", "DDD", "Fuso");

        for(int i = 0; i < cidadesRepetidas; i++) {
            printf("%4d |%10s | %-32s |%11f |%11f |   %s   | %d |%9d |%4d | %-28s |\n",
                i + 1, cidades[i].codigo_ibge, cidades[i].nome, cidades[i].latitude, 
                cidades[i].longitude, cidades[i].capital == 0 ? "Não" : "Sim", cidades[i].codigo_uf,
                cidades[i].siafi_id, cidades[i].ddd, cidades[i].fuso_horario);
        }
        
        do {
            scanf("%d", &escolha);

            if(escolha < 0 && escolha > cidadesRepetidas) {
                printf("Opção inválida!");
            } else {
                printf("Cidade escolhida com sucesso.\n");
                return cidades[escolha - 1].codigo_ibge;
            }
        } while(escolha < 0 && escolha > cidadesRepetidas);

    } else if(cidadesRepetidas == 1) {
        return cidades[0].codigo_ibge;
    } else {
        return NULL;
    }

}

void deletarHash(thash *hash) {
    free(hash->vetor);
}