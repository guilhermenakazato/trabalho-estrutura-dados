#ifndef __LIBGERAL__
#define __LIBGERAL__

#include <stdint.h>

// hash
typedef struct {
    int capital, codigo_uf, siafi_id, ddd;
    double latitude, longitude; 
    char nome[50], fuso_horario[20], codigo_ibge[15];
} tcidade;

typedef struct {
    tcidade *vetor;
    int qtde_elementos;
    int tamanho_max;
    char *(*pegarChave)(tcidade *);
} thash; 

uint32_t hash1(const char *chave, uint32_t seed);
int hash2(const char *chave);
int inserirHash(thash *hash, tcidade *bucket);
int construirHash(thash *hash, char *(*pegarChave)(tcidade *));
tcidade *buscaPorIBGE(thash hash, const char *chave);
tcidade *buscaPorNome(thash hash, const char *chave);
void deletarHash(thash *hash);

// abb
typedef struct _no {
    tcidade cidade;
    struct _no *esq;
    struct _no *dir;
} tnode;

typedef struct {
    tnode *raiz;
} ttree;

typedef struct {
    tcidade cidade;
    double distancia;
} tvizinho;

typedef struct {
    tvizinho *vizinhos;
    int tamanho_max;
    int qtde_elementos;
} theap;

int inserirArvore(ttree *arvore, tnode **atual, tcidade node, int nivel);
tvizinho vizinhosProximos(tnode **atual, tcidade *cidade, int nivel, theap *heap);
void construirArvore(ttree *arvore);
void destruirArvore(tnode **atual);

// heap
int inicializaHeap(theap *heap, int n);
tvizinho acessa_max(tvizinho vetor[]);
void altera_prioridade(tvizinho vetor[], theap heap, int n, tvizinho novoVizinho);
int insere_elemento(tvizinho vetor[], theap *heap, tvizinho novoVizinho);
void heap_sort(tvizinho vetor[], theap heap);

// geral
int lerArquivo(const char *caminhoArquivo, thash *hashIBGE, thash *hashNome, ttree *arvore);

#endif