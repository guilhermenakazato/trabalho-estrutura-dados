#ifndef __LIBGERAL__
#define __LIBGERAL__

// hash
typedef struct {
    int codigo_ibge, capital, codigo_uf, siafi_id, ddd;
    double latitude, longitude; 
    char nome[50], fuso_horario[20];
} tcidade;

typedef struct {
    tcidade *vetor;
    int qtde_elementos;
    int tamanho_max;
} thash; 

int hash1(int chave, int seed, int tamanho_hash);
int hash2(int chave, int tamanho_hash);
int inserirHash(thash *hash, tcidade bucket);
int construirHash(thash *hash);
tcidade *buscarHash(thash hash, int chave);
void deletarHash(thash *hash);

// abb
typedef struct {
    int codigo_ibge;
    double latitude, longitude;
} telementoNo;

typedef struct _no {
    telementoNo elemento;
    struct _no *esq;
    struct _no *dir;
} tnode;

typedef struct {
    tnode *raiz;
} ttree;

typedef struct {
    int codigo_ibge;
    double distancia;
} tvizinho;

int inserirArvore(ttree *arvore, tnode **atual, telementoNo node, int nivel);
tvizinho vizinhosProximos(tnode **atual, tcidade *cidade, int nivel);
void construirArvore(ttree *arvore);

// heap

// geral
int lerArquivo(const char *caminhoArquivo, thash *hash, ttree *arvore);
float preOrdem(tnode **atual, tcidade cidade, float *menor);

#endif