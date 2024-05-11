#include <stdio.h>
#include <stdlib.h>

int main() {
    int *vetor;
    vetor = (int *) calloc(10, sizeof(int));
    vetor[0] = 10;

    printf("%d\n", vetor[0]);
}