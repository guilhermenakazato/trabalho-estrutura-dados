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

void desce(int vetor[], int n, int tamanho_vetor) {
    int esquerdo = filho_esq(n);
    int direito = filho_dir(n);
    int maior = n;

    if(esquerdo < tamanho_vetor && vetor[esquerdo] > vetor[maior]) {
        maior = esquerdo;
    }
    
    if(direito < tamanho_vetor && vetor[direito] > vetor[maior]) {
        maior = direito;
    }

    if(maior != n) {
        troca(&vetor[maior], &vetor[n]);
        desce(vetor, maior, tamanho_vetor);
    }
}

void constroi_heap(int vetor[], int tamanho) {
    int pai_atual = pai(tamanho - 1);

    while(pai_atual >= 0) {
        desce(vetor, pai_atual, tamanho);
        pai_atual--;
    }
}

void sobe(int vetor[], int n) {
    int pos_pai = pai(n);

    if(vetor[n] > vetor[pos_pai]) {
        troca(&vetor[pos_pai], &vetor[n]);
        sobe(vetor, pos_pai);
    }
}

int acessa_max(int vetor[]) {
    return vetor[0];
}

int extrai_max(int vetor[], int *tam) {
    int max = vetor[0];
    vetor[0] = vetor[--*tam];

    desce(vetor, 0, *tam);
    return max;
}

void altera_prioridade(int vetor[], int tamanho, int n, int valor) {
    if(vetor[n] < valor) {
        vetor[n] = valor;
        sobe(vetor, n);
    } else {
        vetor[n] = valor;
        desce(vetor, n, tamanho);
    }
}

int insere_elemento(int vetor[], int *tamanho, int max, int valor) {
    if(*tamanho == max) {
        return EXIT_FAILURE;
    } else {
        vetor[*tamanho] = valor;
        ++*tamanho;

        sobe(vetor, *tamanho - 1);
        return EXIT_SUCCESS;
    }
}

void heap_sort(int vetor[], int tamanho) {
    constroi_heap(vetor, tamanho);

    while(tamanho > 0) {
        troca(&vetor[0], &vetor[--tamanho]);
        desce(vetor, 0, tamanho);
    }
}