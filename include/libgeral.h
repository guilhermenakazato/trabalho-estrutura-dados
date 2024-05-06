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
int inserirHash(thash *hash, tcidade bucket);
int construirHash(thash *hash);
tcidade *buscarHash(thash hash, int chave);
void deletarHash(thash *hash);

typedef struct {
    int codigo_ibge;
    float distancia;
} tvizinho;

typedef struct {
    int codigo_ibge;
    float latitude, longitude;
} elementoNo;

typedef struct _no {
    elementoNo elemento;
    struct _no *esq;
    struct _no *dir;
} tnode;

typedef struct {
    tnode *raiz;
} ttree;

int inserirArvore(ttree *arvore, tnode **atual, elementoNo node, int nivel);
int vizinhosProximos(tnode *atual, tcidade *cidade, int nivel);
void construirArvore(ttree *arvore);

int lerArquivo(const char *caminhoArquivo, thash *hash, ttree *arvore);

#endif