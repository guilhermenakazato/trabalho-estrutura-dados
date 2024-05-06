#include <stdlib.h>
#include <math.h>
#include "../include/libgeral.h"

void construirArvore(ttree *arvore) {
    arvore->raiz = NULL;
}

int inserirArvore(ttree *arvore, tnode **atual, elementoNo node, int nivel) {
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

// pegar codigo retornado pra usar e comparar dps........
int vizinhosProximos(tnode *atual, tcidade *cidade, int nivel) {
    if(atual != NULL) {
        int comp; 

        if(nivel % 2) 
            comp = atual->elemento.longitude - cidade->longitude;
        else 
            comp = atual->elemento.latitude - cidade->latitude;

        float distancia = sqrt(pow(cidade->latitude - atual->elemento.latitude, 2) + pow(cidade->longitude - atual->elemento.longitude, 2));
        if(distancia < menorDistancia) {
            menorDistancia = distancia;
            codigoRetornado = atual->elemento.codigo_ibge;
        }

        if(comp > 0) {
            vizinhosProximos(atual->esq, cidade, ++nivel, menorDistancia);
        } else {    
            vizinhosProximos(atual->dir, cidade, ++nivel, menorDistancia);
        }   
    }
}