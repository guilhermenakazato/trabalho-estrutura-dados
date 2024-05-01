#ifndef __LIBGERAL__
#define __LIBGERAL__

typedef struct {
    int codigo_ibge, capital, codigo_uf, siafi_id, ddd;
    float latitude, longitude; 
    char nome[50], fuso_horario[20];
} tcidade;

typedef struct {
    tcidade *vetor;
    int qtde_elementos;
    int tamanho_max;
} thash; 


int hash1(int chave, int seed, int tamanho_hash);
int hash2(int chave, int tamanho_hash);
int inserir(thash *hash, tcidade bucket, int numCidade);
int construir(thash *hash);
tcidade *buscar(thash hash, int chave);
int lerArquivo(const char *caminhoArquivo, thash *hash);

#endif