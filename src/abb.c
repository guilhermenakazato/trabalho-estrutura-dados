#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../include/libgeral.h"

void construirArvore(ttree *arvore) {
    arvore->raiz = NULL;
}

int inserirArvore(ttree *arvore, tnode **atual, telementoNo node, int nivel) {
    if(*atual == NULL) {
        *atual = malloc(sizeof(tnode));
        (*atual)->elemento = node;
        (*atual)->esq = NULL;
        (*atual)->dir = NULL;

        return EXIT_SUCCESS;
    } else {
        int resultadoComp;
        
        if(nivel % 2) 
            resultadoComp = (*atual)->elemento.longitude - node.longitude;
        else 
            resultadoComp = (*atual)->elemento.latitude - node.latitude;

        if(resultadoComp < 0) {
            inserirArvore(arvore, &(*atual)->dir, node, ++nivel);
        } else {
            inserirArvore(arvore, &(*atual)->esq, node, ++nivel);
        }
    }

    return EXIT_FAILURE;
}

tvizinho comparaMinDistancia(tvizinho vizinho1, tvizinho vizinho2) {
    if(vizinho1.distancia < vizinho2.distancia)
        return vizinho1;

    return vizinho2;
}

tvizinho vizinhosProximos(tnode **atual, tcidade *cidade, int nivel, theap *heap) {
    float distancia; 
    tvizinho maisProximo;
    maisProximo.distancia = 999999999;

    if(*atual != NULL) {
        int comp;   

        if(nivel % 2)
            comp = (*atual)->elemento.longitude - cidade->longitude;
        else 
            comp = (*atual)->elemento.latitude - cidade->latitude;
        
        distancia = sqrt(pow(cidade->latitude - (*atual)->elemento.latitude, 2) + pow(cidade->longitude - (*atual)->elemento.longitude, 2));

        if(distancia < maisProximo.distancia && distancia > 0) {
            maisProximo.distancia = distancia;
            maisProximo.codigo_ibge = (*atual)->elemento.codigo_ibge;        
        }

        if(comp < 0) {
            maisProximo = comparaMinDistancia(maisProximo, vizinhosProximos(&(*atual)->dir, cidade, ++nivel, heap));
            
            if(maisProximo.distancia > comp || heap->qtde_elementos != heap->tamanho_max)
                maisProximo = comparaMinDistancia(maisProximo, vizinhosProximos(&(*atual)->esq, cidade, ++nivel, heap));
            
        } else {
            maisProximo = comparaMinDistancia(maisProximo, vizinhosProximos(&(*atual)->esq, cidade, ++nivel, heap));

            if(maisProximo.distancia > comp || heap->qtde_elementos != heap->tamanho_max)
                maisProximo = comparaMinDistancia(maisProximo, vizinhosProximos(&(*atual)->dir, cidade, ++nivel, heap));
        }
    }

    if(heap->qtde_elementos != heap->tamanho_max) {
        printf("Hello\n");
        insere_elemento(heap->vizinhos, heap, maisProximo);
        printf("Pos 0: %d\n", heap->vizinhos[0].codigo_ibge);
        printf("Mais proximo: %d\n", maisProximo.codigo_ibge);
    } else if(maisProximo.distancia < acessa_max(heap->vizinhos).distancia) {
        altera_prioridade(heap->vizinhos, *heap, 0, maisProximo);
        printf("Pos 0: %d\n", heap->vizinhos[0].codigo_ibge);
    }

    return maisProximo;
}