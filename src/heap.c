#include <stdlib.h>
#include "../include/libgeral.h"

void troca(int *pos1, int *pos2) {
    int temp = *pos1;
    *pos1 = *pos2;
    *pos2 = temp;
}

int pai(int pos_filho) {
    return pos_filho == 0 ? 0 : (int) (pos_filho - 1) / 2;
}

int filho_esq(int pos_pai) {
    return pos_pai * 2 + 1;
}

int filho_dir(int pos_pai) {
    return pos_pai * 2 + 2;
}

void desce(tvizinho vetor[], int n, theap heap) {
    int esquerdo = filho_esq(n);
    int direito = filho_dir(n);
    int maior = n;

    if(esquerdo < heap.qtde_elementos && vetor[esquerdo].distancia > vetor[maior].distancia) {
        maior = esquerdo;
    }
    
    if(direito < heap.qtde_elementos && vetor[direito].distancia > vetor[maior].distancia) {
        maior = direito;
    }

    if(maior != n) {
        troca(&vetor[maior], &vetor[n]);
        desce(vetor, maior, heap);
    }
}

void constroi_heap(tvizinho vetor[], theap heap) {
    int pai_atual = pai(heap.qtde_elementos - 1);

    while(pai_atual >= 0) {
        desce(vetor, pai_atual, heap);
        pai_atual--;
    }
}

void sobe(tvizinho vetor[], int n) {
    int pos_pai = pai(n);

    if(vetor[n].distancia > vetor[pos_pai].distancia) {
        troca(&vetor[pos_pai], &vetor[n]);
        sobe(vetor, pos_pai);
    }
}

tvizinho acessa_max(tvizinho vetor[]) {
    return vetor[0];
}

tvizinho extrai_max(tvizinho vetor[], theap *heap) {
    tvizinho max = vetor[0];
    heap->qtde_elementos--;
    vetor[0] = vetor[heap->qtde_elementos];

    desce(vetor, 0, *heap);
    return max;
}

void altera_prioridade(tvizinho vetor[], theap heap, int n, tvizinho novoVizinho) {
    if(vetor[n].distancia < novoVizinho.distancia) {
        vetor[n] = novoVizinho;
        sobe(vetor, n);
    } else {
        vetor[n] = novoVizinho;
        desce(vetor, n, heap);
    }
}

int insere_elemento(tvizinho vetor[], theap *heap, tvizinho novoVizinho) {
    if(heap->qtde_elementos == heap->tamanho_max) {
        return EXIT_FAILURE;
    } else {
        vetor[heap->qtde_elementos] = novoVizinho;
        heap->qtde_elementos += 1;

        sobe(vetor, heap->qtde_elementos - 1);
        return EXIT_SUCCESS;
    }
}

void heap_sort(tvizinho vetor[], theap heap) {
    constroi_heap(vetor, heap);

    while(heap.qtde_elementos > 0) {
        heap.qtde_elementos--;
        troca(&vetor[0], &vetor[heap.qtde_elementos]);
        desce(vetor, 0, heap);
    }
}