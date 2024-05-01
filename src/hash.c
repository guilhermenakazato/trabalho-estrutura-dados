#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libgeral.h"
#define SEED 239
#define SIZE 10007

int hash1(int chave, int seed, int tamanho_hash) {
    return (chave * seed) % tamanho_hash;
}

int hash2(int chave, int tamanho_hash) {
    return 1 + (chave % (--tamanho_hash));
}

int construir(thash *hash) {
    hash->vetor = (tcidade *) calloc(SIZE, sizeof(tcidade));
    if(hash->vetor == NULL) {
        return EXIT_FAILURE;
    }

    hash->qtde_elementos = 0;
    hash->tamanho_max = SIZE;

    return EXIT_SUCCESS;
}

int inserir(thash *hash, tcidade bucket, int numCidade) {
    int pos;
    int i = 0;

    do {
        int resultadoHash1 = hash1(bucket.codigo_ibge, SEED, hash->tamanho_max);
        int resultadoHash2 = hash2(bucket.codigo_ibge, hash->tamanho_max);
        pos = (resultadoHash1 + i * resultadoHash2) % hash->tamanho_max;

        i++;
    } while(hash->vetor[pos].codigo_ibge != 0);

    hash->vetor[pos] = bucket;
    hash->qtde_elementos += 1;

    return EXIT_SUCCESS;
}

tcidade *buscar(thash hash, int chave) {
    int pos;

    do {
        int i = 0;
        int resultadoHash1 = hash1(chave, SEED, hash.tamanho_max);
        int resultadoHash2 = hash2(chave, hash.tamanho_max);
        int pos = (resultadoHash1 + i * resultadoHash2) % hash.tamanho_max;
    
        if(chave == hash.vetor[pos].codigo_ibge)
            return &hash.vetor[pos];
    } while(hash.vetor[pos].codigo_ibge != 0);

    return NULL;
}